# NOTES
 ``` some notes for implementation improvements and design ```
 

 
# stateless
 * makte as much as possible stateless, like no dependancy to the asio::io_service with timers 



# TODO - next setps
 - [ ] apdu controller add timeout handling for confirmed services
 - [ ] service controller manage handel hasking for doi
 - [ ] error handling !
 - [ ] add information to the README.md
 - [ ] example script as client, sending reinit, write properties, and others in sequence if successful 
 - [ ] simple bacnet-browser:
 		- send who-is, 
 		- try to read all properties of each device 
 		- build json-structure
 - [ ] bacnet-device:
 		- implement idea of one function for each read-prop/write-prop
 		- example on how to answer to read/write
 		- 
 - [ ] support for segmentation
  		- make it configurable
  		- write unit-tests
  		- try with example-device
 		


 