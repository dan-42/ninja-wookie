# NOTES
 ``` some notes for implementation improvements and design ```
 
# callback manager
 * NPDU -layer
 * APDU -layer
 * Service -Layer
 
# stateless
 * makte as much as possible stateless, like no dependancy to the asio::io_service with timers
  
# parsing tags
 create boost spirit terminals like word24bit and one for tag one for unsigned
 to use it, you could to  tag[unsigned]
 the parser would parse the tag_id and the flag context or application tag
 the it would iterare depending on the length inside the tag over te unsigned value
 
 generation could be similar. By passing the unsgigned to tag tag grammar, 
 the tag ca know the length to integrate it inside of it.



# TODO
 * create a managing class, for invoke id's
   goal, sending a reinitialize_device and giving a handler which will return the answer, not just when it was send successful.
   possible problems, depending on the answer is will be an ACK, Error PDU
 
  So answer could be  SUCCESS, ERROR_password, errror_...
  page 573:   16.4.1.3.1 Error Type
  
 how if it is not a simple ack expected?  design for other frames should be consindered
  
  steps:
  * write c++11 interface how it should look like
  * review
  * try to make it work :-)


  *idea: use templates for a uniqe property like
     uint32 pv_poperty = 80
  
    typedef pv bacnet::property<pv_property, float, is_writable>;
    open questions: how to combine a whole object?
    how to manage read or write property? and multiple?
    where is the logic, like cant write pv when not out_of_service
    so all musst be combined in one object?
    how to manage reusability and seperation for object specifics but DRY!
 