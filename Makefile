FILESERVER =
FILECLIENT =

server: monServer.c
	gcc monServer.c -o server

client: monClient.c
	gcc monClient.c -o client

run: server client $(FILESERVER)
	gnome-terminal -- ./se $(FILESERVER)
	gnome-terminal -- ./cl $(FILECLIENT)
