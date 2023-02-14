# Clone Reference
Allows you to create multiple references to a single userdata object, which can be useful in certain scenarios

# What exactly is Clone Reference in a more detailed way?
'cloneref' clones a reference from one userdata to another in Luau. Takes 1 argument as userdata, and its value is used to look up the corresponding reference in a table stored in Engine's registry. The reference stored in the table is then removed, and the original userdata is pushed onto the stack, along with a new reference stored in the table using the original userdata's value as the key

# How do I exactly find "push_instance" ?
Search up the string 'InvalidInstance' in IDA, the function the string is located in is the function you're looking for

# How do I know cloneref actually clones anything?
I have included another function called 'compareinstances' so you can use that to see if cloneref actually clones anything, for more info, you can test using Unified Name Convention's environment check script

# Side NOTE!
This is meant for cheats, its for a specific game that I would like to not say its name in order to avoid any trouble :D
