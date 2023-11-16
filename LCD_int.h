#ifndef LCD_INT_H
#define LCD_INT_H

void LCD_voidInit(void);
void LCD_voidSendData(u8 LCD_u8_Data);
void LCD_voidSendCommand(u8 LCD_u8_Command);
void lcdPrint(char *str);

#endif