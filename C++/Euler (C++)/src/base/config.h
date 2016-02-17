#ifndef __CONFIG_H__
#define __CONFIG_H__

#define CONFIGFILE "solver.cfg"

#include <map>
#include <string>
#include "answers.h"

class Config
{
   private:
      Config();
      bool readConfig();
      std::map<std::string, std::string> values;
      int loglvl;
      bool onlyfastest;
      std::string answerFile;
      Answers *answers;

      Config(Config const&);
      void operator=(Config const&);

   public:
      static Config& Instance()
      {
         static Config instance;
         return instance;
      }

      std::string getValue(std::string key);
      static std::string Answer(int num)
      {
         return Instance().answers->getAnswer(num);
      }
      static int LOGLVL()
      {
         return Instance().loglvl;
      }
      static bool ONLYFASTEST()
      {
      	return Instance().onlyfastest;
      }
};

#endif
