//
// Created by dan on 8/23/15.
//

#ifndef NINJA_WOOKIE_BOOLEAN_APPLICATION_GRAMMAR_HPP
#define NINJA_WOOKIE_BOOLEAN_APPLICATION_GRAMMAR_HPP



#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>


namespace bacnet { namespace  apdu { namespace detail { namespace type { namespace parser {

          using namespace boost::spirit;
          using namespace boost::spirit::qi;
          using namespace boost::phoenix;

          using boost::spirit::qi::bit_field;
          using boost::spirit::qi::rule;
          using boost::spirit::qi::_1;
          using boost::phoenix::bind;




          template<typename Iterator>
          struct boolean_application_grammar : grammar<Iterator, bool()> {

            rule<Iterator, bool()>     bool_rule;
            rule<Iterator, bool()>     application_tagged_rule;
            rule<Iterator, bool()>     application_tagged_true_rule;
            rule<Iterator, bool()>     application_tagged_false_rule;

            boolean_application_grammar() : boolean_application_grammar::base_type(bool_rule){

              constexpr uint8_t encoded_application_tagged_true  = 0x11;
              constexpr uint8_t encoded_application_tagged_false = 0x10;

              bool_rule  = application_tagged_rule;

              application_tagged_rule = application_tagged_true_rule
                                        | application_tagged_false_rule;

              application_tagged_true_rule = byte_(encoded_application_tagged_true)[_val = true];
              application_tagged_true_rule = byte_(encoded_application_tagged_false)[_val = false];

            }
          };
}}}}}

/*
namespace bacnet { namespace  apdu { namespace detail { namespace type {  namespace generator {

                    using namespace boost::spirit;
                    using namespace boost::spirit::karma;
                    using namespace boost::phoenix;

                    using boost::spirit::karma::bit_field;
                    using boost::spirit::karma::rule;
                    using boost::spirit::karma::_1;

                    using namespace bacnet::apdu::detail::type;


                    template<typename Iterator>
                    struct null_grammar : grammar<Iterator, null_t() >{

                        static constexpr uint8_t encoded_null = 0x00;

                        rule<Iterator, null_t()>     null_rule;


                        null_grammar() : null_grammar::base_type(null_rule){

                            null_rule  = byte_(encoded_null);
                            null_rule.name("null_rule");

                        }
                    };

                }}}}}

*/











#endif //NINJA_WOOKIE_BOOLEAN_APPLICATION_GRAMMAR_HPP
