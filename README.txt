by John David Vidad

code works by accepting 1 command at a time to create a thread for the command, then it will wait for another command after creating a thread for the previous command.
It works concurrently but it does not handle sync problems or locks in general.
