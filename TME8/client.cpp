#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
  int port = atoi(argv[1]);

  sockaddr_in dest;
  dest.sin_port = htons(port);
  dest.sin_addr.s_addr = INADDR_ANY;
  dest.sin_family = AF_INET;

  int sock = socket(AF_INET, SOCK_STREAM, 0);
  int c = connect(sock, (struct sockaddr *)&dest, sizeof(dest));
  cout << "connected to server on " << port << endl;

  cout << "0: LIST, 1: UPLOAD, 2: DOWNLOAD" << endl;
  string input;
  cin >> input;

  char msg = atoi(input.data());
  // cout << msg << endl;
  write(sock, &msg, sizeof(msg));
  int reponse_size;
  read(sock, &reponse_size, sizeof(int));

  char *reponse = new char[reponse_size];
  size_t bytes_read = read(sock, reponse, reponse_size);
  string rep_string(reponse);

  cout << rep_string << endl;

  delete[] reponse;
  shutdown(sock, 0);
  close(sock);
}