//
// Created by dan on 10/4/15.
//


namespace  bacnet { namespace apdu { namespace type {
static bacnet::binary_data generate(const bacnet::apdu::type::tag &tag_) {
  using namespace bacnet::apdu;
  bacnet::binary_data binary;

  std::back_insert_iterator<bacnet::binary_data> sink(binary);
  type::detail::generator::tag_grammar<decltype(sink)> generator;
  bool result = false;
  try {
    result = boost::spirit::karma::generate(sink, generator, tag_);
  }
  catch (std::exception &e) {
    std::cerr << "exception: apdu generate  unsigned_integer" << e.what() << std::endl;
  }
  if (!result) {
    return bacnet::binary_data();
  }

  return binary;
}


static bool parse(bacnet::binary_data& data, bacnet::apdu::type::tag &tag_) {
  using namespace bacnet::apdu;

  using namespace bacnet::apdu;

  auto start = data.begin();
  auto end = data.end();

  type::detail::parser::tag_grammar<decltype(start)> parser;
  bool has_succeeded = false;
  try {
    has_succeeded = boost::spirit::qi::parse(start, end, parser, tag_);
  }
  catch (std::exception &e) {
    std::cerr << "exception: cant parse tag" << e.what() << std::endl;
  }
  if (has_succeeded) {
    data.erase(data.begin(), start);
    return true;
  }
  return false;
}


}}}


bacnet::apdu::type::tag tag_simple;
bacnet::apdu::type::tag tag_parsed;
tag_simple.is_context_tag(false);
tag_simple.number(12);
tag_simple.length_value_type(4);

std::cout << std::endl;
std::cout << "-----simple-----------------"  << std::endl;
std::cout << "TAG: " << tag_simple << std::endl;

auto generated = bacnet::apdu::type::generate(tag_simple);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;


bacnet::apdu::type::tag tag_extended_number;
tag_extended_number.is_context_tag(false);
tag_extended_number.number(15);
tag_extended_number.length_value_type(4);

std::cout << std::endl;
std::cout << std::endl;
std::cout << "-----tag_extended_number---15--------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;

generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;



tag_extended_number.number(16);
tag_extended_number.length_value_type(4);

std::cout << std::endl;
std::cout << "-----tag_extended_number----16-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;

generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;

tag_extended_number.number(17);
tag_extended_number.length_value_type(4);

std::cout << std::endl;
std::cout << "-----tag_extended_number----17-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;

generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;

tag_extended_number.number(254);
tag_extended_number.length_value_type(4);
std::cout << std::endl;
std::cout << "-----tag_extended_number----254-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;

generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;



std::cout << std::endl;
tag_extended_number.number(12);
tag_extended_number.length_value_type(4);
std::cout << std::endl;
std::cout << "-----tag_extended_length----4-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;

tag_extended_number.number(12);
tag_extended_number.length_value_type(5);
std::cout << std::endl;
std::cout << "-----tag_extended_length----5-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;

tag_extended_number.number(12);
tag_extended_number.length_value_type(6);
std::cout << std::endl;
std::cout << "-----tag_extended_length----6-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;


tag_extended_number.number(12);
tag_extended_number.length_value_type(253);
std::cout << std::endl;
std::cout << "-----tag_extended_length----253-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;

tag_extended_number.number(12);
tag_extended_number.length_value_type(254);
std::cout << std::endl;
std::cout << "-----tag_extended_length----254-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;



tag_extended_number.number(12);
tag_extended_number.length_value_type(255);
std::cout << std::endl;
std::cout << "-----tag_extended_length----255-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;


tag_extended_number.number(12);
tag_extended_number.length_value_type( 65534 );
std::cout << std::endl;
std::cout << "-----tag_extended_length----65534-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;


tag_extended_number.number(12);
tag_extended_number.length_value_type(65535);
std::cout << std::endl;
std::cout << "-----tag_extended_length----65535-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;

tag_extended_number.number(12);
tag_extended_number.length_value_type(65536);
std::cout << std::endl;
std::cout << "-----tag_extended_length----65536-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;

tag_extended_number.number(12);
tag_extended_number.length_value_type(65537);
std::cout << std::endl;
std::cout << "-----tag_extended_length----65537-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;





tag_extended_number.number(12);
tag_extended_number.length_value_type(4294967294);
std::cout << std::endl;
std::cout << "-----tag_extended_length----4294967294-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;


tag_extended_number.number(12);
tag_extended_number.length_value_type(4294967295);
std::cout << std::endl;
std::cout << "-----tag_extended_length----4294967295-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;




std::cout << std::endl;
std::cout << std::endl;
tag_extended_number.number(254);
tag_extended_number.length_value_type(4294967295);
std::cout << std::endl;
std::cout << "--tag_extended_number 254---tag_extended_length----4294967295-------------"  << std::endl;
std::cout << "TAG: " << tag_extended_number << std::endl;
generated = bacnet::apdu::type::generate(tag_extended_number);
for(auto &c : generated){
std::cout << " 0x" << std::hex << (int)c ;
}
std::cout << std::endl;
tag_parsed = bacnet::apdu::type::tag{};
if( bacnet::apdu::type::parse(generated, tag_parsed)) {
std::cout << " parsed successfull " << tag_parsed << std::endl;
}
else
std::cout << " parsed failed " << std::endl;
