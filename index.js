// Watch the points for a ClassDojo user and publish Particle events
// when the count changes

require('dotenv').config();

const Particle = require('particle-api-js');
const particle = new Particle();

const rp = require('request-promise-native');
const request = rp.defaults({ jar: true });

// Environment
const particle_token = process.env['PARTICLE_TOKEN'];
const fetchInterval = +(process.env['FETCH_INTERVAL'] || 30) * 1000;
const dojo = {
  user: process.env['CLASSDOJO_USER'],
  password: process.env['CLASSDOJO_PASSWORD'],
  parent: process.env['CLASSDOJO_PARENT_ID'],
};

particle.getEventStream({ deviceId: 'mine', name: 'fetchDojoPoints', auth: particle_token })
.then(stream => {
  console.log('Subscribed to Particle event');
  stream.on('event', data => {
    console.log('Received Particle event to fetch Dojo Points');
    fetchDojoPoints({ forcePublish: true });
  });
});

setInterval(fetchDojoPoints, fetchInterval);
fetchDojoPoints();

function fetchDojoPoints({ forcePublish } = {}) {
  console.log('Fetching points');
  request(`https://home.classdojo.com/api/parent/${dojo.parent}/student`, {
    json: true
  })
  .then(data => {
    return processDojoPoints(data, { forcePublish });
  }, err => {
    if (err && err.statusCode === 401) {
      return loginDojo().then(() => fetchDojoPoints({ forcePublish }));
    } else {
      console.log('UNKNOWN ERROR WHILE FETCHING POINTS');
      console.error(err);
    }
  }).catch(err => console.error(err));
}

function loginDojo() {
  return request.post('https://home.classdojo.com/api/dojoSession', {
    body: {
      login: dojo.user,
      password: dojo.password
    },
    json: true
  }).then(data => {
    console.log('Login to ClassDojo successful');
  }, err => {
    console.err('LOGIN TO CLASSDOJO FAILED!');
    console.log(err);
  });
}

const dojoPoints = {};
function processDojoPoints(data, { forcePublish } = {}) {
  const changedPoints = [];
  data._items.forEach(student => {
    const name = `${student.firstName} ${student.lastName}`;
    const points = student.currentPoints;

    if (dojoPoints[name] != points || forcePublish) {
      changedPoints.push(name);
    }
    dojoPoints[name] = points;
  });

  return Promise.all(changedPoints.map(name => {
    const points = dojoPoints[name];
    console.log(`Publishing ${points} for ${name}`);
    return particle.publishEvent({ name: `dojoPoints/${name}`, data: points, auth: particle_token });
  }));
}
