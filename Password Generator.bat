@ECHO OFF
COLOR 0A
 
echo This is the random password generator

set /p length_pass="Enter password length: "
 
set use_symbol_en_small=yes
set use_symbol_en_big=yes
set use_symbol_numbers=yes
set use_symbol_special=yes
 
 

set number_symbol_in_use=0
 

set group_en_small=a d c d e f g h i j k l m n o p q r s t u v w x y z
set group_en_big=A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
set group_ru_small=а б в г д е ё ж з и й к л м н о п р с т у ф х ц ч ш щ ъ ы ь э ю я
set group_ru_big=А Б В Г Д Е Ё Ж З И Й К Л М Н О П Р С Т У Ф Х Ц Ч Ш Щ Ъ Ы Ь Э Ю Я
set group_numbers=0 1 2 3 4 5 6 7 8 9
set group_special=~ ! ? # $ / \ + - _ . '
 
:: узнаём кол-во символов которые будут использоваться и составляем строку выбора
if %use_symbol_en_small%==yes (
    set /a number_symbol_in_use=%number_symbol_in_use%+26
    set symbol_in_use=%group_en_small%
)
if %use_symbol_en_big%==yes (
    set /a number_symbol_in_use=%number_symbol_in_use%+26
    set symbol_in_use=%symbol_in_use% %group_en_big%
)
if %use_symbol_numbers%==yes (
    set /a number_symbol_in_use=%number_symbol_in_use%+10
    set symbol_in_use=%symbol_in_use% %group_numbers%
)
if %use_symbol_special%==yes (
    set /a number_symbol_in_use=%number_symbol_in_use%+16
    set symbol_in_use=%symbol_in_use% %group_special%
)
 
:: вычисляем интервал принадлежащий одному символу
set /a symbol_step_random=32767/%number_symbol_in_use%
 

for /l %%a in (1,1,%length_pass%) do call :randominaze %RANDOM%
 
echo Your random password:   %passkey%
 
pause>nul
 
exit /b 0
 
:randominaze
 
set randomnumber=%RANDOM%
set cycle_number=0
set previous_number_letter=0
for %%b in (%symbol_in_use%) do call :division %%b
exit /b 0
 
:division
set letter=%1
set /a cycle_number=%cycle_number%+1
set /a number_letter=%symbol_step_random%*%cycle_number%
if /i %randomnumber% LEQ %number_letter% (
    if /i %randomnumber% GTR %previous_number_letter% (
        set passkey=%passkey%%letter%
    )
)
set previous_number_letter=%number_letter%
exit /b 0