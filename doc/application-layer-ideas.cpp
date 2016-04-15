




struct read_prop_req {
	object_id;
	propert_id;
	array_index;
};


struct read_prop_ack {
	object_id;/// tag0
	propert_id; ///1
	array_index; ///2 optional
	any_data; ///3
};

struct write_prop {
	object_id;/// tag0
	propert_id; ///1
	array_index; ///2 optional
	any_data; ///3
	priority ///4 //optional
};



struct object {
	
	std::pair<value, error> read_prop(propert_id, array_index idx) {
	  
	  //check if request is valid
	  //look up property;
	  
	  auto binary_data = generate(property) //generated application-tag and value	 
	 
	}
	
	 error write_prop(propert_id, array_index idx, any_value, priority) {
	  
	  //check if request is valid
	  value = parse(any_value, context);
	  //set property
	 
		return;
	}
}



struct service_controller{

void register_callbacks();

void send_asnwer();

};




// device
struct application_controller {

service_controller service_controller;

service_controller.register_callbacks(
	[&](read_prop_req req, meta_info mi){
	
	
	//check has_read_prop()
	auto& object = object_list.find(req.object_id);
	auto value = object.read_prop(propert_id, array_index);
	
	
	
	//OK
	read_prop_ack ack(req, value);
	service_controller.send_answer(ack, mi);
	
	//ERROR
	error er;
	service_controller.send_answer(er, mi);
	},
	[&](write_prop req, meta){
	
	//check has_write_prop()
	auto& object = object_list.find(req.object_id);
	auto success = object.write_prop(propert_id, array_index);
	
	send_answer()
	}
);


};
