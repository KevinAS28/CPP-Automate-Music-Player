#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <errno.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <string>
#include <cstring>

std::string readFilee(char name[])
{
	std::fstream file = std::fstream(name, std::ios::in);
	std::string result;
	char temp;
	while (1)
	{
		temp = file.get();
		if (temp==EOF|temp=='\0'=='\n')
		{
			break;
		}
		result+=temp;
	}
	file.close();
	return result;
}
char **result;
char** split_str(const char *str0, const char *str1)
{
	char **to_return = (char**) calloc(sizeof(char*), 1);
	int i = 0, a = 0, d = 0;
	to_return[0] = (char*)calloc(sizeof(char), 1);
	for (; i < strlen(str0); i ++)
	{
		if (str0[i]==str1[0])
		{
			//possibilities
			int salah = 0;
			for (int b = i, c = 0; b < strlen(str1); b++)
			{
				if (str1[c]!=str0[b])
				{
					salah=1;
					break;
				}
				c++;
			}
			if (!salah)
			{

				a++;
				d=0;
				to_return = (char**)realloc(to_return, sizeof(char*)*(a+1));
				to_return[a] = (char*)calloc(sizeof(char), 1);
				i+=strlen(str1)-1;
				continue;
			}
		}
		to_return[a][d] = str0[i];
		d++;
		to_return[a] = (char*)realloc(to_return[a], sizeof(char)*(d+1));
	}
	result = to_return;
	return to_return;
}
void pulseaudio()
{
	system("pulseaudio");
}
int main(int argv, char* args[])
{
	if (!(argv>1))
	{
		std::cout << "By Kevin Agusto-8 April 2018\nProgram for playing my musiccc";
		return 0;
	}
	if (0==atoi(args[1]))
	{
		char command[] = "killall vlc";
		system(command);
		return 0;
	}
/*
	pid_t pid = fork();
	if ((int)pid > 0)
	{
		//child
		pulseaudio();
	}
*/
	char nama[] = "/root/programming/cpp_saya/mymusic.list";
	char* file = split_str((readFilee(nama).c_str()), "\n")[atoi(args[1])];
	char command[1000];
	sprintf(command, "vlc /root/Music/%s", file);
	printf("Executing...%s\n", command);
	system(command);
	free(file);
	return 0;
}
