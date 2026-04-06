#ifdef __linux__
#include <linux/limits.h>
#elif __APPLE__
#include <sys/syslimits.h>
#else
#include <limits.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

// https://github.com/thieman/docker/blob/master/pkg/namesgenerator/names-generator.go
char *left[] = {
    "admiring",      "adoring",  "agitated",  "angry",      "backstabbing",
    "berserk",       "boring",   "clever",    "cocky",      "compassionate",
    "condescending", "cranky",   "desperate", "determined", "distracted",
    "dreamy",        "drunk",    "ecstatic",  "elated",     "elegant",
    "evil",          "fervent",  "focused",   "furious",    "gloomy",
    "goofy",         "grave",    "happy",     "high",       "hopeful",
    "hungry",        "insane",   "jolly",     "jovial",     "kickass",
    "lonely",        "loving",   "mad",       "modest",     "naughty",
    "nostalgic",     "pensive",  "prickly",   "reverent",   "romantic",
    "sad",           "serene",   "sharp",     "sick",       "silly",
    "sleepy",        "stoic",    "stupefied", "suspicious", "tender",
    "thirsty",       "trusting",
};
#define LEFT_SIZE 57

char *right[] = {
    "albattani",  "almeida",   "archimedes", "ardinghelli", "babbage",
    "banach",     "bardeen",   "brattain",   "shockley",    "bartik",
    "bell",       "blackwell", "bohr",       "brown",       "carson",
    "colden",     "cori",      "cray",       "curie",       "darwin",
    "davinci",    "einstein",  "elion",      "engelbart",   "euclid",
    "fermat",     "fermi",     "feynman",    "franklin",    "galileo",
    "goldstine",  "goodall",   "hawking",    "heisenberg",  "hodgkin",
    "hoover",     "hopper",    "hypatia",    "jang",        "jones",
    "kilby",      "noyce",     "kirch",      "kowalevski",  "lalande",
    "leakey",     "lovelace",  "lumiere",    "mayer",       "mccarthy",
    "mcclintock", "mclean",    "meitner",    "mestorf",     "morse",
    "newton",     "nobel",     "payne",      "pare",        "pasteur",
    "perlman",    "pike",      "poincare",   "poitras",     "ptolemy",
    "ritchie",    "thompson",  "rosalind",   "sammet",      "sinoussi",
    "stallman",   "swartz",    "tesla",      "torvalds",    "turing",
    "wilson",     "wozniak",   "wright",     "yalow",       "yonath",
};

#define RIGHT_SIZE 80

#if defined(__linux__) || defined(__APPLE__) || defined(UNIX) ||               \
    defined(__FreeBSD__) || defined(__OpenBSD__)
#define MKDIR(p, n) mkdir(p, n)
#else
#define MKDIR(p, n) mkdir(p)
#endif

int main(void) {
  srand(time(NULL));

  char *l = left[rand() % LEFT_SIZE];
  char *r = right[rand() % RIGHT_SIZE];

  char cwd[PATH_MAX];

  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    fprintf(stderr, "Can't get current directory.");
  }

  char *path = malloc(sizeof(char) * PATH_MAX);

  sprintf(path, "%s/%s_%s", cwd, l, r);

  struct stat s = {0};

  if (stat(path, &s) == -1) {
    MKDIR(path, 0700);
    printf("%s\n", path);
  }
}
