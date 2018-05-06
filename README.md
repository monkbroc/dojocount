# Dojo Count

## Deploy

The cloud app is deployed to Digital Ocean to onephotoaday.dyndns.org

## Notes

### Login
```
curl 'https://home.classdojo.com/api/dojoSession' -H 'origin: https://www.classdojo.com' -H 'accept-encoding: gzip, deflate, br' -H 'accept-language: en-US,en;q=0.8,fr-CA;q=0.6,fr;q=0.4' -H 'user-agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.90 Safari/537.36' -H 'content-type: application/json' -H 'accept: application/json' -H 'referer: https://www.classdojo.com/' -H 'authority: home.classdojo.com' -H 'cookie: amplitude_idclassdojo.com=eyJkZXZpY2VJZCI6IjFmMzdiZmM2LTM2YTktNGQ3MS04MGMwLWNjODUwZmE0NWY2ZlIiLCJ1c2VySWQiOm51bGwsIm9wdE91dCI6ZmFsc2UsInNlc3Npb25JZCI6MTUwNDgzNDAxOTIyNywibGFzdEV2ZW50VGltZSI6MTUwNDgzNDAxOTIzMiwiZXZlbnRJZCI6MSwiaWRlbnRpZnlJZCI6MCwic2VxdWVuY2VOdW1iZXIiOjF9; _ga=GA1.2.818857885.1504834020; _gid=GA1.2.63657291.1504834020; _gat_UA-25121690-1=1' --data-binary '{"login":"jvanier@gmail.com","password":"password","resumeAddClassFlow":false}' --compressed
```

Response
```
set-cookie:dojo_home_login.sid=s%3ADl15KWUT1sS2MwpmNB6SGrYETRU7PrqB.KvK%2BMrhsVKAFrOhuHAzQmHo9OSqcsLVLW6jdAIkfCHo; Max-Age=31536000; Domain=.classdojo.com; Path=/; Expires=Sat, 08 Sep 2018 01:27:20 GMT; HttpOnly; Secure
set-cookie:dojo_login.sid=s%3ADl15KWUT1sS2MwpmNB6SGrYETRU7PrqB.KvK%2BMrhsVKAFrOhuHAzQmHo9OSqcsLVLW6jdAIkfCHo; Domain=.classdojo.com; Path=/; Expires=Sat, 08 Sep 2018 01:27:20 GMT; HttpOnly; Secure
```

