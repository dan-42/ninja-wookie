# NOTES
 ``` some notes for implementation improvements and design ```
 
# parsing
 create boost spirit terminals like word24bit and one for tag one for unsigned
 to use it, you could to  tag[unsigned]
 the parser would parse the tag_id and the flag context or application tag
 the it would iterare depending on the length inside the tag over te unsigned value
 
 generation could be similar. By passing the unsgigned to tag tag grammar, 
 the tag ca know the length to integrate it inside of it.
