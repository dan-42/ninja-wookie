# NOTES
 ``` some notes for implementation improvements and design ```
 

 
# stateless
 * makte as much as possible stateless, like no dependancy to the asio::io_service with timers 



# TODO - next setps
 - [ ] apdu controller add timeout handling for confirmed services
 - [ ] service controller manage handel hasking for doi
 - [ ] error handling !
  - [ ] make enumerated grammar parse generate from/to  enumerated type
  - [ ] add print function for enumerated
  - [ ] add print function for error -> to_json from pre
  - [ ] add test for type::error with and without test
  - [ ] add error-test with reinitialize device test
  - [ ] improve example reinitialize device with printing error or success 
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
 		


 