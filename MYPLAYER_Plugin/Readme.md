<a name="head.MyPlayer_Plugin"></a>
# MyPlayer Plugin

**Version: 1.0**

**Status: :black_circle::black_circle::black_circle:**

MyPlayer plugin for Thunder framework.

## Methods:
```
curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc":"2.0", "id":1, "method":"MyPlayer.1.setUrl" , "params":{"url":"file:///home/raj/Downloads/sintel_trailer-480p.webm"} }' http://127.0.0.1:55555/jsonrpc
curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc":"2.0", "id":1, "method":"MyPlayer.1.play"}' http://127.0.0.1:55555/jsonrpc
curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc":"2.0", "id":1, "method":"MyPlayer.1.pause"}' http://127.0.0.1:55555/jsonrpc
curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc":"2.0", "id":1, "method":"MyPlayer.1.exit"}' http://127.0.0.1:55555/jsonrpc
curl --header "Content-Type: application/json" --request POST --data '{"jsonrpc":"2.0", "id":1, "method":"MyPlayer.1.loop","params":{"repeat":"1"}}' http://127.0.0.1:55555/jsonrpc
```

## Responses:
```
setUrl:
{"jsonrpc":"2.0","id":1,"result":{"message":"set path"}}

play:
{"jsonrpc":"2.0","id":1,"result":{"message":"video play"}}

pause:
{"jsonrpc":"2.0","id":1,"result":{"message":"video pause"}}

exit:
{"jsonrpc":"2.0","id":1,"result":{"message":"player exit"}}

loop:
{"jsonrpc":"2.0","id":1,"result":{"message":"loop mode on"}}
```
