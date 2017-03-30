# checkedRM

 Check the path that is going to be deleted and issue an alert when some dangerous operations is detected. Prevent system from user's misoperations.
 
------

## Install

> make 

> make install

------
## Uage

> cr [OPTION]... [FILE]...

> the same as 'rm'

## Example
```

~$ cr -fr ~/Desktop/test/*
This operation may be harmful to system! Please confirm!(y/n)y
~$ cr -fr /
This operation may be harmful to system! Please confirm!(y/n)n
Abort!
~$

```
