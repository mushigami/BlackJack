
#ifndef __UTILS_H__
#define __UTILS_H__

enum CharacterCaseType
{
	CC_UPPER_CASE= 0,
	CC_LOWER_CASE,
	CC_EITHER
};

const char * INPUT_ERROR_STRING = "Input error! Please try again.";

char GetCharacter(const char * prompt, const char* error);
char GetCharacter(const char *prompt, const char* error, const char validInput[], int validInputLength, CharacterCaseType charCase);

int GetInteger(const char * prompt, const char* error, const int validInput[], int validInputLength);
bool WantToPlayAgain();

void ClearScreen();
void WaitForKeyPress();

#endif
