# Rainbow Dialogue
Format text file into a colorful dialogue.

## Contribution
This project requires gnu make and a c compiler.

### Build
```
$ make
```

### Run
```
$ build/rainbow-dialogue kaomoji.txt
```
and start typing in text.

OR

Try piping into rainbow-dialogue from other commands. For example:
```
$ ls | build/rainbow-dialogue kaomoji.txt
```
```
$ cat LICENSE | build/rainbow-dialogue kaomoji.txt
```
```
$ df -h | build/rainbow-dialogue kaomoji.txt
```