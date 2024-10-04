Determine if a path is valid or invalid, 
where: 
 - Valid paths can be files or directories.
 - If the path is to a file, the file cannot already exist but must be creatable AND writeable.
 - If the path is to a directory, the directory must already exist AND be writeable.

Build: `gcc file-or-dir -o fod`
Usage: `fod [file | directory]`
