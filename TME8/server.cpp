#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dirent.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

string file_names() {
  DIR *dir;
  if ((dir = opendir("./dir")) == NULL) {
    perror("Cannot open ./dir");
    exit(1);
  }
  string names;
  struct dirent *dp;
  while ((dp = readdir(dir)) != NULL) {
    string name(dp->d_name);
    names += name + "\n";
  }
  return names;
}

int main(int argc, char *argv[]) {
  int port = atoi(argv[1]);
  char *dossier = argv[2];

  int sc = socket(AF_INET, SOCK_STREAM, 0);
  int scom;
  struct sockaddr_in sa;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = INADDR_ANY;
  sa.sin_family = AF_INET;

  int socklen = sizeof(sa);

  int b = bind(sc, (struct sockaddr *)&sa, socklen);
  listen(sc, 10);
  cout << "listening on: " << port << endl;

  while (true) {
    scom = accept(sc, (struct sockaddr *)&sa, (socklen_t *)&socklen);
    char c;
    read(scom, &c, sizeof(char));

    string reponse;
    switch (c) {
    case 0: {
      cout << "LIST" << endl;
      reponse = file_names();
      break;
    }
    case 1:
      cout << "UPLOAD" << endl;
      reponse = 'U';
      break;
    case 2:
      cout << "DOWNLOAD" << endl;
      reponse = 'D';
      break;
    }
    int rep_size = reponse.size();
    write(scom, &rep_size, sizeof(int));
    write(scom, reponse.data(), rep_size);
    shutdown(scom, 2);
    close(scom);
  }
  close(sc);
}
