Some Notes for the BACnetStack
=============================


naming
------
 * ninja-wookie -- fun but strange



structure
---------

### properties
need to be accessed via ```bacnet::property::present_value```
need to be user extendable -> no enum class?

### layers

### updv4

### updv6

#### bvllv4 / bvllv6  

#### npdu

#### apdu
 
### BBMD stuff


file and folder structure
-------------------------

examples

bacnet::bvlc::frame::result
bacnet::bvlc::frame::write-boradcast-distribution-table
bacnet::bvlc::frame::read-boradcast-distribution-table
bacnet::bvlc::frame::read-boradcast-distribution-table-ack
bacnet::bvlc::frame::...



bacnet::npdu::

bacnet::apdu::


bacnet::service::who_is

bacnet::config::stack
	* send I-am as broadcast resonse
	


bacnet::config::device
	* network number
	* device id
	* segmentation
	* vendor_id
	* max_apdu length
	
	



## Interfaces
 using boost::static_visitors<> as api interface? might be cool idea?
 why do i neer seperate byte_ rule for parsing into std::string
 

 
 
 
 
 
 # callback way
 
 BVLL
 	* async_read(cb(binarydata))
 		* parse 
 		* send to npdu (binary data)  unicast or broadcast
 	
NPDU
	* unicast(binary data)
		* parse
		* if for apdu_layer send to apdu (meta_data, binary_data)
		
	* broadcast(binary data)
		* parse
		* if for apdu_layer send to apdu (meta_data, binary_data)
 
APDU
	* callback(meta_data, binary_data)
		* parse apdu_static_part
			use one 8bit for pdu_type and control information, but define more then one memeberfunction to access the same bit
			write parser for apdu_static part, like the header of the npdu
			write tests for it, use examples from the standrad, one for each pdu_type at least
		
		
		* apply visit for pdu/service type (meta_data, pdu, remaining binary_data)
		
SERVICES
	* 
		 
 
 