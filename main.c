#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void open(char[], char[]);
char* makeHTMLTimeString();
void trimstr(char[]);

int main(int argc, char *argv[]) {
  if (argc == 3) {
    //printf("%s", argv[1]);
  }
  
  open(argv[1], argv[2]);
  
  return 0;
}

void open(char infile[], char outfile[]) {
  FILE *infp, *outfp, *tmpfp;

  infp  = fopen(infile, "r");
  outfp = fopen(outfile, "r+");
  tmpfp = tmpfile();
  unsigned char count = 0;

  char buffer[1024];

  while(fgets(buffer, 1024, outfp) != NULL) {
    fprintf(tmpfp, "%s", buffer);
    if(count == 0 && (strstr(buffer, "<!-- entry -->")) != NULL) {
      // entry found, insert new entry
      fgets(buffer, 1024, infp);
      fprintf(tmpfp, "      %s", "<div class=\"entry\">\n");
      // get title from first line
      trimstr(buffer);
      fprintf(tmpfp, "        <h2>%s</h2>\n", buffer);
      // insert timestamp
      char * timestr;
      timestr = makeHTMLTimeString();
      fprintf(tmpfp, "        %s", timestr);
      free(timestr);

      while(fgets(buffer, 1024, infp)){
        trimstr(buffer);
        fprintf(tmpfp, "        <p>%s</p>\n", buffer); 
      }

      fprintf(tmpfp, "      %s", "</div>\n      <!-- end entry -->\n");
      fprintf(tmpfp, "      %s", "<!-- entry -->\n");
      count++;
    }
  }
  rewind(tmpfp);
  rewind(outfp);
  char c;
  while((c=getc(tmpfp)) != EOF) {
    putc(c,outfp);
  }

  fclose(tmpfp);
  fclose(infp);
  fclose(outfp);
}

char * makeHTMLTimeString() {
  time_t rawtime;
  struct tm *thetime;
  char *timestr;
  timestr = (char*) calloc(256, sizeof(char));

  time(&rawtime);
  thetime = localtime(&rawtime);

  strftime(timestr, 256, "<p class=\"post-date\">%A %B %e at %r (GMT-5:00)</p>\n", thetime);
  return timestr;
}

void trimstr(char str[]) {
  str[strlen(str) -1] = 0;
}
