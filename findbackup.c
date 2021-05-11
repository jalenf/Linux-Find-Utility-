#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

void display_all_files(char *sub_dir);
void find_file_name(char *sub_dir, char *file_name);
void find_file_time(char *sub_dir, char *time_modified);
void find_file_inode(char *sub_dir, int i_node);
void remove_file_name(char *sub_dir, char *file_name);
void remove_file_time(char *sub_dir, char *time_modified);

int main(int argc, char *argv[]) //define the main to take in arguments
{
    char *sub_dir = argv[2];

    //if part 1 - display_all_files
    if(argc == 3)
    {
        display_all_files(sub_dir);
    }
    //if part 2
    else if(argc == 5)
    {
        char *arg4 = argv[4];
        //if part 2.1 - find_file_name
        if(strcmp(argv[3], "-name") == 0)
        {
            find_file_name(sub_dir, arg4);
        }
        //if part 2.2 - find_file_time
        else if(strcmp(argv[3], "-mmin") == 0)
        {
            find_file_time(sub_dir, arg4);
        }
        //if part 2.3 - find_file_inode
        else if(strcmp(argv[3], "-inum") == 0)
        {
           int inum = atoi(arg4); //convert the inoum stirng on numbers to int
           find_file_inode(sub_dir, inum);
        }
        else
        {
            return 0;
        }
    }
    //if part 3
        else if(argc == 6)
    {
        if(strcmp(argv[5], "-delete") == 0) //compare strings and if equal
        {
            char *arg4 = argv[4]; //set the pointer to the full string
            //if part 3 - remove_file_name
            if(strcmp(argv[3], "-name") == 0)
            {
                remove_file_name(sub_dir, arg4); //pass in the directory and the string
            }
            //if part 3 - remove_time
            else if(strcmp(argv[3],"-mmin") == 0)
            {
                remove_file_time(sub_dir, arg4);
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

//part 1 - find where-to-look
void display_all_files (char *sub_dir)
{
    DIR *sub_dp=opendir(sub_dir);//open a directory stream at dir name
    struct dirent * sub_dirp; //define the next directory entry (NULL if no further entry) 
    struct stat buf;//define a file status structure
    char temp1[]=".";
    char temp2[]="..";
	
    //check whether the directory stream is opened successfully
    if(sub_dp!=NULL)
    {
        // read one entry each time
        while((sub_dirp=readdir(sub_dp))!=NULL) // readdir returns a pointer to a 'dirent' representinng the next entry pointed to by a 'dirp'.
        {
            //check whether the first entry is a subdirectory
            char *temp =sub_dirp->d_name;

            //to avoid recursively searching . and .. in the directory.
            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
            {
                char temp3[]="/";
                char *temp_sub = temp3;
                temp_sub=strcat(temp_sub,temp);

                //now you add the / in front of the entrys name
                char *temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);
                //now you get a full path, e.g., testdir/dir1 or testdir/test1

                // try to open
                DIR *subsubdp=opendir(temp_full_path);
                //if not null, means we find a subdirectory, otherwise, its just a file
                if(subsubdp!=NULL){
                    //close the stream, because we will reopen it in the recursive call.
                    closedir(subsubdp);
                    display_all_files(temp_full_path);//call the recursive function call.
                }
                else
                {
                    printf("%s\n",temp_full_path);
                }
            }
        }//end of while loop
        closedir(sub_dp);//close the steam
    }
    else
    {
        printf("cannot open directory\n");
        exit(2);
    }
}


//part 2.1 - find where-to-look-name
void find_file_name(char *sub_dir, char *file_name)
{
	DIR *sub_dp=opendir(sub_dir);//open a directory stream at dir name
    struct dirent * sub_dirp; //define the next directory entry (NULL if no further entry) 
    struct stat buf;//define a file status structure
    char temp1[]=".";
    char temp2[]="..";
	
    //check whether the directory stream is opened successfully
    if(sub_dp!=NULL)
    {
        // read one entry each time
        while((sub_dirp=readdir(sub_dp))!=NULL) // readdir returns a pointer to a 'dirent' representinng the next entry pointed to by a 'dirp'.
        {
            //check whether the first entry is a subdirectory
            char *temp =sub_dirp->d_name;

            //to avoid recursively searching . and .. in the directory.
            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
            {
                char temp3[]="/";
                char *temp_sub = temp3;
                temp_sub=strcat(temp_sub,temp);

                //now you add the / in front of the entrys name
                char *temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);
                //now you get a full path, e.g., testdir/dir1 or testdir/test1

                // try to open
                DIR *subsubdp=opendir(temp_full_path);
                //if not null, means we find a subdirectory, otherwise, its just a file
                if(subsubdp!=NULL){
                    //close the stream, because we will reopen it in the recursive call.
                    closedir(subsubdp);
                     find_file_name(temp_full_path, file_name);//call the recursive function call.
                }
                else
                {
                    if(strcmp(temp, file_name) == 0)
                    {
						printf("%s\n",temp_full_path);
                    }
                }
            }
        }//end of while loop
        closedir(sub_dp);//close the steam
    }
    else
    {
        printf("cannot open directory\n");
        exit(2); 
    }
}

//part 2.2 - find where-to-look-mmin
void find_file_time(char *sub_dir, char *time_modified)
{
	DIR *sub_dp=opendir(sub_dir);//open a directory stream at dir name
    struct dirent * sub_dirp; //define the next directory entry (NULL if no further entry) 
    struct stat buf;//define a file status structure
    char temp1[]=".";
    char temp2[]="..";
	
    //check whether the directory stream is opened successfully
    if(sub_dp!=NULL)
    {
        // read one entry each time
        while((sub_dirp=readdir(sub_dp))!=NULL) // readdir returns a pointer to a 'dirent' representinng the next entry pointed to by a 'dirp'.
        {
            //check whether the first entry is a subdirectory
            char *temp =sub_dirp->d_name;

            //to avoid recursively searching . and .. in the directory.
            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
            {
                char temp3[]="/";
                char *temp_sub = temp3;
                temp_sub=strcat(temp_sub,temp);

                //now you add the / in front of the entrys name
                char *temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);
                //now you get a full path, e.g., testdir/dir1 or testdir/test1

                // try to open
                DIR *subsubdp=opendir(temp_full_path);
                //if not null, means we find a subdirectory, otherwise, its just a file
                if(subsubdp!=NULL){
                    //close the stream, because we will reopen it in the recursive call.
                    closedir(subsubdp);
                    find_file_time(temp_full_path, time_modified);//call the recursive function call.
                }
                else
                {
					if(stat(temp_full_path,&buf)==0)
					{
						//compare time of temp (the file) with the passed time
						time_t mmin;
						time(&mmin);
						double timedifference = (difftime(buf.st_mtime, mmin));
						//if mmin is -n						
						if(strcmp("-10", time_modified) == 0)
						{
							if(timedifference > 10.0)
							{
									printf("Time last modified %d\n", buf.st_mtime);
									printf("%s\n",temp_full_path);
							}
						}
						//if mmin is +n	
						else if(strcmp("+10", time_modified) == 0)
						{
							if(timedifference < 10.0)
							{
									printf("Time last modified %d\n", buf.st_mtime);
									printf("%s\n",temp_full_path);
							}
						}						
						//if mmin is n
						else
						{
							if(timedifference == 0.0)
							{
									printf("Time last modified %d\n", buf.st_mtime);								
									printf("%s\n",temp_full_path);
							}							
						}
					}
                }
            }
        }//end of while loop
        closedir(sub_dp);//close the steam
    }
    else
    {
        printf("cannot open directory\n");
        exit(2); 
    }
}

//part 2.3 - find where-to-look-inum
void find_file_inode(char *sub_dir, int i_node)
{
	DIR *sub_dp=opendir(sub_dir);//open a directory stream at dir name
    struct dirent * sub_dirp; //define the next directory entry (NULL if no further entry) 
    struct stat buf;//define a file status structure
    char temp1[]=".";
    char temp2[]="..";
	
    //check whether the directory stream is opened successfully
    if(sub_dp!=NULL)
    {
        // read one entry each time
        while((sub_dirp=readdir(sub_dp))!=NULL) // readdir returns a pointer to a 'dirent' representinng the next entry pointed to by a 'dirp'.
        {
            //check whether the first entry is a subdirectory
            char *temp =sub_dirp->d_name;

            //to avoid recursively searching . and .. in the directory.
            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
            {
                char temp3[]="/";
                char *temp_sub = temp3;
                temp_sub=strcat(temp_sub,temp);

                //now you add the / in front of the entrys name
                char *temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);
                //now you get a full path, e.g., testdir/dir1 or testdir/test1

                // try to open
                DIR *subsubdp=opendir(temp_full_path);
                //if not null, means we find a subdirectory, otherwise, its just a file
                if(subsubdp!=NULL){
                    //close the stream, because we will reopen it in the recursive call.
                    closedir(subsubdp);
                    find_file_inode(temp_full_path, i_node);//call the recursive function call.
                }
                else
                {
					//compare inode
					if(stat(temp_full_path,&buf)==0)
					{
						if((int)buf.st_ino == i_node)
						{
								printf("Inode is %d\n", (int)buf.st_ino);
								printf("%s\n",temp_full_path);
						}
					}
                }
            }
        }//end of while loop
        closedir(sub_dp);//close the steam
    }
    else
    {
        printf("cannot open directory\n");
        exit(2); 
    }
}

//part 3 - find where-to-look-remove-name
void remove_file_name(char* sub_dir, char *file_name)
{
	DIR *sub_dp=opendir(sub_dir);//open a directory stream at dir name
    struct dirent * sub_dirp; //define the next directory entry (NULL if no further entry) 
    struct stat buf;//define a file status structure
    char temp1[]=".";
    char temp2[]="..";
	
    //check whether the directory stream is opened successfully
    if(sub_dp!=NULL)
    {
        // read one entry each time
        while((sub_dirp=readdir(sub_dp))!=NULL) // readdir returns a pointer to a 'dirent' representinng the next entry pointed to by a 'dirp'.
        {
            //check whether the first entry is a subdirectory
            char *temp =sub_dirp->d_name;

            //to avoid recursively searching . and .. in the directory.
            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
            {
                char temp3[]="/";
                char *temp_sub = temp3;
                temp_sub=strcat(temp_sub,temp);

                //now you add the / in front of the entrys name
                char *temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);
                //now you get a full path, e.g., testdir/dir1 or testdir/test1

                // try to open
                DIR *subsubdp=opendir(temp_full_path);
                //if not null, means we find a subdirectory, otherwise, its just a file
                if(subsubdp!=NULL){
                    //close the stream, because we will reopen it in the recursive call.
                    closedir(subsubdp);
                    remove_file_name(temp_full_path, file_name);//call the recursive function call.
                }
                else 
                {
                    if(strcmp(temp, file_name) == 0)
                    {
							printf("%s\n",temp_full_path);
							printf("Remove %s\n", temp_full_path);
							remove(temp_full_path);
                    }
                }
            }
        }//end of while loop
        closedir(sub_dp);//close the steam
    }
    else
    {
        printf("cannot open directory\n");
        exit(2); 
    }
}

//part 3 - find where-to-look-remove-time
void remove_file_time(char *sub_dir, char *time_modified)
{
	DIR *sub_dp=opendir(sub_dir);//open a directory stream at dir name
    struct dirent * sub_dirp; //define the next directory entry (NULL if no further entry) 
    struct stat buf;//define a file status structure
    char temp1[]=".";
    char temp2[]="..";
	
    //check whether the directory stream is opened successfully
    if(sub_dp!=NULL)
    {
        // read one entry each time
        while((sub_dirp=readdir(sub_dp))!=NULL) // readdir returns a pointer to a 'dirent' representinng the next entry pointed to by a 'dirp'.
        {
            //check whether the first entry is a subdirectory
            char *temp =sub_dirp->d_name;

            //to avoid recursively searching . and .. in the directory.
            if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
            {
                char temp3[]="/";
                char *temp_sub = temp3;
                temp_sub=strcat(temp_sub,temp);

                //now you add the / in front of the entrys name
                char *temp_full_path=malloc(sizeof(char)*2000);
                temp_full_path=strcpy(temp_full_path,sub_dir);
                strcat(temp_full_path,temp_sub);
                //now you get a full path, e.g., testdir/dir1 or testdir/test1

                // try to open
                DIR *subsubdp=opendir(temp_full_path);
                //if not null, means we find a subdirectory, otherwise, its just a file
                if(subsubdp!=NULL){
                    //close the stream, because we will reopen it in the recursive call.
                    closedir(subsubdp);
                    remove_file_time(temp_full_path, time_modified);//call the recursive function call.
                }
                else
                {
					//compare time of temp (the file) with the passed time
					if(stat(temp_full_path,&buf)==0)
					{
						//compare time of temp (the file) with the passed time
						time_t mmin;
						time(&mmin);
						double timedifference = (difftime(buf.st_mtime, mmin));
						//if mmin is -n	
						
						if(strcmp("-10", time_modified) == 0)
						{
							if(timedifference > 10.0)
							{
							printf("Time last modified %d\n", buf.st_mtime);
							printf("%s\n",temp_full_path);
							printf("Remove %s\n", temp_full_path);
							remove(temp_full_path);								}
						}
						//if mmin is +n	
						else if(strcmp("+10", time_modified) == 0)
						{
							if(timedifference < 10.0)
							{
							printf("Time last modified %d\n", buf.st_mtime);
							printf("%s\n",temp_full_path);
							printf("Remove %s\n", temp_full_path);
							remove(temp_full_path);								}
						}						
						//if mmin is n
						else
						{
							if(timedifference == 0.0)
							{
							printf("Time last modified %d\n", buf.st_mtime);
							printf("%s\n",temp_full_path);
							printf("Remove %s\n", temp_full_path);
							remove(temp_full_path);								}							
						}						
					}
                }
            }
        }//end of while loop
        closedir(sub_dp);//close the steam
    }
    else
    {
        printf("cannot open directory\n");
        exit(2); 
	}
}
