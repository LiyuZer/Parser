#include <unordered_map>
#include <string>
#include <vector>
#include "../utilities/utilities.h"
#include "grammar_def.h"
using namespace std;

/*
Sample grammer 

program : IDENTIFIER : [a]
All grammars should start with program, or else the parser will not work
*/

std::unordered_map<std::string, std::vector<SymbolPtr> > rules = {
    {"program", {
        CreateRule("alienDef"),
        CreateSpecialSymbol('+'),
        CreateRule("missionDef"),
        CreateSpecialSymbol('+'),
        CreateRule("galacticRules"),
        CreateSpecialSymbol('?'),
    }},
    {"alienDef", {
        CreateToken("ALIEN"), // Keyword for defining aliens
        CreateToken("IDENTIFIER"), // Alien's name
        CreateToken("HAS"),
        CreateToken("LEFT_BRACE"),
        CreateRule("alienAbilities"),
        CreateToken("RIGHT_BRACE"),
    }},
    {"alienAbilities", {
        CreateParen('('),
        CreateRule("abilityStatement"),
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("abilityStatement"),
        CreateParen(')'),
        CreateSpecialSymbol('?'),
        CreateParen(')'),
        CreateSpecialSymbol('*'), // Allow multiple abilities

    }},
    {"abilityStatement", {
        CreateToken("IDENTIFIER"), // Ability name
        CreateToken("COLON"),
        CreateRule("abilityType"),
    }},
    {"abilityType", {
        CreateToken("SUPER_SPEED"),
        CreateOr(),
        CreateToken("INVISIBILITY"),
        CreateOr(),
        CreateToken("LASER_EYES"),
        CreateOr(),
        CreateToken("TELEPORTATION"),
    }},
    {"missionDef", {
        CreateToken("MISSION"), // Keyword for defining missions
        CreateToken("IDENTIFIER"), // Mission name
        CreateToken("LEFT_BRACE"),
        CreateRule("missionDetails"),
        CreateToken("RIGHT_BRACE"),
    }},
    {"missionDetails", {
        CreateToken("TO"),
        CreateToken("IDENTIFIER"), // Destination
        CreateToken("WITH"),
        CreateRule("missionCrew"),
        CreateToken("FOR"),
        CreateToken("INTEGER_LITERAL"), // Time duration
        CreateToken("DAYS"),
    }},
    {"missionCrew", {
        CreateToken("LEFT_BRACKET"),
        CreateRule("alienList"),
        CreateToken("RIGHT_BRACKET"),
    }},
    {"alienList", {
        CreateToken("IDENTIFIER"), // Alien name
        CreateParen('('),
        CreateToken("COMMA"),
        CreateToken("IDENTIFIER"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
    }},
    {"galacticRules", {
        CreateToken("GALACTIC_RULES"),
        CreateToken("LEFT_BRACE"),
        CreateRule("ruleStatement"),
        CreateToken("RIGHT_BRACE"),
    }},
    {"ruleStatement", {
        CreateToken("DO_NOT"),
        CreateRule("prohibitedAction"),
        CreateToken("ON"),
        CreateToken("IDENTIFIER"), // Planet name
    }},
    {"prohibitedAction", {
        CreateToken("FIGHT"),
        CreateOr(),
        CreateToken("STEAL"),
        CreateOr(),
        CreateToken("DISRESPECT_EARTHLINGS"),
    }},
};
