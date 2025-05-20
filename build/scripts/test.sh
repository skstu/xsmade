curl "https://www.google.com/search?q=%E4%BD%A0%E5%A5%BD" \
  -H "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36" \
  -H "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8" \
  -H "Accept-Language: en-US,en;q=0.9" \
  -H "Connection: keep-alive" \
  -H "Referer: https://www.google.com/" \
  -b "/C/Users/k34ub/Desktop/google.txt" \
  -L -o "/C/Users/k34ub/Desktop/google.html"
