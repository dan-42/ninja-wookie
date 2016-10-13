# NOTES
 ``` some notes for implementation improvements and design ```
 

 
# stateless
 * makte as much as possible stateless, like no dependancy to the asio::io_service with timers 


# implemented services
## SENDING
 - [x] who_is
 - [x] i_am
 - [x] reinitialize_device
 - [x] read_prop_request
 - [x] read_prop_ack

## RECEIVINNG 
 - [x] who_is
 - [x] i_am
 - [x] reinitialize_device
 - [x] read_prop_request
 - [x] read_prop_ack


## B-ASC
 - DS-RP-B
  - execute ReadProperty
  
 - DS-WP-B
  - execute WriteProperty
  
 - DM-DDB-B
  - execute whoIs
  - initiate iAm
  
 - DM-DOB-B
   - execute whoHas
   - initiate iHave
   
 - DM-DCC-B
   - execute DeviceCommunicationControl
 
 


# TODO - next setps
 -  [ ]  apdu controller add timeout handling for confirmed services 
 - [x] service controller manage handel hasking for doi 
 - [x] error handling ! 
  - [x] make enumerated grammar parse generate from/to enumerated type 
  - [x] add print function for enumerated 
  - [x] add print function for error -> to_json from pre 
  - [x] add test for type::error with and without test 
  - [x] add error-test with reinitialize device test 
  - [x] improve example reinitialize device with printing error or success 
 - [ ] add information to the README.md 
 - [x] read_property-service
 - [x] read_property client  example
 - [ ] who-has service
 - [ ] i-have service
 - [ ] example script as client, sending reinit, write properties, and others in  sequence if successful 
 - [ ] simple bacnet-browser:
 		-  send who-is,
 		-  try to read all properties of each device
 		-  build json-structure 
 - [ ] bacnet-device:
 		-  implement idea of one function for each read-prop/write-prop
 		- example on how to answer to read/write
 		- 
 - [ ] support for segmentation
  		- make it configurable
  		- write unit-tests
  		- try with example-device
 		


 