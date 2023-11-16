#define F_CPU 8000000UL
#include <string.h> // Added for strcmp()
#include "Includes.h"

#define Max_len 5

#define state_GET_USERNAME 0
#define state_GET_PASS	   1
#define state_VALID		   2

const char Username[Max_len] = "ABC", Password[Max_len] = "953";

void get_username();
void get_password();
void get_validation();
void reset_system();

int STATE = 0;

int main(void)
{
	
	LCD_voidInit();
	KEYPAD_voidInit();
	
	while(1)
	{
		u8 key = KEYPAD_u8GetButton();
		switch(STATE)
		{
			case state_GET_USERNAME:
			get_username();
			break;

			case state_GET_PASS:
			get_password();
			break;

			case state_VALID:
			get_validation();
			break;
		}
		
		if(key == '*') reset_system();
	}

	return 0;
}

void reset_system()
{
	LCD_voidSendCommand(0x01);
}

void get_username()
{
	lcdPrint("Username: ");
	
	char user[Max_len];
	int i = 0;

	while(1)
	{
		char key = KEYPAD_u8GetButton();

		if(key=='#')
		{
			user[i] = '\0';
					if(strcmp(Username, user) == 0)
					{
						STATE = state_GET_PASS;
						LCD_voidSendCommand(0xC0);
						break;
					}
					else
					{
						STATE = state_GET_USERNAME;
						LCD_voidSendCommand(0x01);
						break;
					}
		}
		
		else if ((key != '\0') && (i < Max_len))
		{
			user[i++] = key;
			LCD_voidSendData(key);
			_delay_ms(200);
		}
	}
}


void get_password() {

lcdPrint("Password: ");

char pass[Max_len];
int i = 0;

while(1)
{
	char key = KEYPAD_u8GetButton();

	if(key=='#')
	{
		pass[i] = '\0';
		if(strcmp(Password, pass) == 0)
		{
			STATE = state_VALID;
			LCD_voidSendCommand(0x01);
			break;
		}
		else
		{
			STATE = state_GET_PASS;
			LCD_voidSendCommand(0x01);
			break;
		}
	}
	
	else if ((key != '\0') && (i < Max_len))
	{
		pass[i++] = key;
		LCD_voidSendData(key);
		_delay_ms(200);
	}
}
}


void get_validation() {

	if(STATE == state_VALID) {
		LCD_voidSendCommand(0x01);
		lcdPrint("Login Successful");
	}
	else {
		LCD_voidSendCommand(0x01);
		lcdPrint("Invalid Login");
	}

	STATE = state_GET_USERNAME; 
}