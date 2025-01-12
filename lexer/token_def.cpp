#include <unordered_map>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "token_def.h"

/*
You can add custom tokens here, only caveat is that you have to add the token to the lexer as well. 
Also operators have maximum two characters, if you want to add more than two characters then you have to
add a new token to the lexer. 
*/
using namespace std;

std::unordered_map<std::string, std::string> keywords = {
    {"super_speed", "SUPER_SPEED"},
    {"invisibility", "INVISIBILITY"},
    {"laser_eyes", "LASER_EYES"},
    {"teleportation", "TELEPORTATION"},
    {"mission", "MISSION"},
    {"to", "TO"},
    {"with", "WITH"},
    {"for", "FOR"},
    {"days", "DAYS"},
    {"galactic_rules", "GALACTIC_RULES"},
    {"do_not", "DO_NOT"},
    {"fight", "FIGHT"},
    {"steal", "STEAL"},
    {"disrespect_earthlings", "DISRESPECT_EARTHLINGS"},
    {"true", "TRUE"},
    {"false", "FALSE"},
    {"on", "ON"}, 
    {"alien", "ALIEN"},
    {"has", "HAS"}

};

std::unordered_map<std::string, std::string> operators = {
    {"->", "ARROW"},
    {"=>", "ARROW_EQUALS"},
    {"(", "LEFT_PAREN"},
    {")", "RIGHT_PAREN"},
    {"[", "LEFT_BRACKET"},
    {"]", "RIGHT_BRACKET"},
    {"{", "LEFT_BRACE"},
    {"}", "RIGHT_BRACE"},
    {"+", "PLUS"},
    {"-", "MINUS"},
    {"*", "STAR"},
    {"/", "DIV"},
    {"%", "MOD"},
    {"&&", "AND"},
    {"||", "OR"},
    {"~", "TILDE"},
    {"!", "NOT"},
    {"=", "ASSIGN"},
    {"<", "LESS"},
    {">", "GREATER"},
    {"==", "EQUAL"},
    {"!=", "NOT_EQUAL"},
    {"<=", "LESS_EQUAL"},
    {">=", "GREATER_EQUAL"},
    {";", "SEMICOLON"},
    {":", "COLON"},
    {",", "COMMA"},
    {".", "DOT"}
};
