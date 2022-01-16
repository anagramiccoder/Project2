by John David Vidad
this code was tested on Ubuntu 14.04.1, or the default kernel from installing in Lab 0 ( not the modified kernel)

code works by accepting 1 command at a time to create a thread for the command, then it will wait for another command after creating a thread for the previous command.
It works concurrently but it does not handle sync problems or locks in general. The command input does not record \n in the input, but the "\n" serves as an identifier of the ending of a command

note: no spaces allowed specially in the path.
--the read command
after a 1 or 6 second delay, will read the contnet of the given directory. in case the file is not present will print FILE DNE as result in the read.txt file.
in case the file is present but is empty, will print <blank> as a result in read.txt file ( since it was not stated how it will be handled).

--the write command
after 1 or 6 second delay, will append letter per letter of the given string to the path indicated. in case file does not exist, it will create a new file in the given path and write the string letter per letter with 25 ms interval each.

-- the empty command
after 1 or 6 second delay, it will check if file exists using the 'r' identifier. if the file is present and has content, will save the content to empty.txt and empties the file. then wait for 7- 10 seconds. in case the file exists and does not have a content or the file does not even exist, the program will apend "FILE ALREADY EMPTY" as result in the empty.txt, and will not wait for 7-10 seconds.

extra command 'exit'

added an extra command so that we can wait for the threads to finish before exiting the program and not abruptly end the program using ctrl +c.
