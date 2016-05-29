/*
 * category.hpp
 *
 *  Created on: May 29, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_ERROR_CATEGORY_HPP_
#define SRC_BACNET_ERROR_CATEGORY_HPP_

#include <boost/system/error_code.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/error/error_class.hpp>
#include <bacnet/error/error_code.hpp>
#include <bacnet/error/reject_reason.hpp>
#include <bacnet/error/abort_reason.hpp>

#include <bacnet/type/enumerated.hpp>
#include <bacnet/type/object_identifier.hpp>
namespace bacnet {
////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// simple bacnet error
    struct error_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::error"; }
      std::string message(int ev) const { return err::error_code::to_string(ev); }

      static inline std::string message(int e_code, int e_class) {
        return err::error_class::to_string(e_class) + "::" + err::error_code::to_string(e_code);
      }

    };
    inline const boost::system::error_category & bacnet_error_category() noexcept  {
      static const error_category bacnet_category_const;
      return bacnet_category_const;
    }



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////  bacnet error on list changes
    struct  change_list_error_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::change_list_error"; }
      std::string message(int ev) const { return err::error_code::to_string(ev); }

      static inline std::string message(int e_code, int e_class, uint32_t first_failed_element_number) {
        return err::error_class::to_string(e_class) + "::" + err::error_code::to_string(e_code) + "::element(" + std::to_string(first_failed_element_number) + ")";
      }

    };
    inline const boost::system::error_category & bacnet_change_list_error_category() noexcept  {
      static const change_list_error_category change_list_error_category_const;
      return change_list_error_category_const;
    }



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////  bacnet error on object changes
    struct  create_object_error_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::create_object_error"; }
      std::string message(int ev) const { return err::error_code::to_string(ev); }

      static inline std::string message(int e_code, int e_class, uint32_t first_failed_element_number) {
        return err::error_class::to_string(e_class) + "::" + err::error_code::to_string(e_code) + "::element(" + std::to_string(first_failed_element_number) + ")";
      }

    };
    inline const boost::system::error_category & bacnet_create_object_error_category() noexcept  {
      static const create_object_error_category create_object_error_category_const;
      return create_object_error_category_const;
    }



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////  bacnet error on object changes
    ///xxx create this type object_property_reference
    struct object_property_reference{
      bacnet::type::object_identifier object_identifier;
      bacnet::type::enumerated        property_identifier;
      boost::optional<uint32_t>       property_array_index;
    };
    struct  write_property_multiple_error_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::create_object_error"; }
      std::string message(int ev) const { return err::error_code::to_string(ev); }

      static inline std::string message(int e_code, int e_class, object_property_reference first_failed_write_attempt) {
        return     err::error_class::to_string(e_class)
          + "::" + err::error_code::to_string(e_code)
          + "::" + std::to_string(first_failed_write_attempt.object_identifier.to_native());
      }

    };
    inline const boost::system::error_category & bacnet_write_property_multiple_error_category() noexcept  {
      static const write_property_multiple_error_category write_property_multiple_error_category_const;
      return write_property_multiple_error_category_const;
    }




////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////  bacnet error on object changes
    ///xxx create this type confirmed_private_transfer_error_t
    struct  confirmed_private_transfer_error_t {
      uint16_t vendor_id;
      uint32_t service_number;
      bacnet::binary_data parameter;
    };
    struct  confirmed_private_transfer_error_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::confirmed_private_transfer_error"; }
      std::string message(int ev) const { return err::error_code::to_string(ev); }

      static inline std::string message(int e_code, int e_class, confirmed_private_transfer_error_t confirmed_private_transfer_error_) {
        return err::error_class::to_string(e_class) + "::" + err::error_code::to_string(e_code) + ":: xxx to do";
      }

    };
    inline const boost::system::error_category & bacnet_confirmed_private_transfer_error_category() noexcept  {
      static const confirmed_private_transfer_error_category confirmed_private_transfer_error_category_const;
      return confirmed_private_transfer_error_category_const;
    }



////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////  bacnet error vt_close_error
    struct  vt_close_error {
        std::vector<uint8_t> list_Of_vt_session_identifiers;
    };
    struct  vt_close_error_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::vt_close_error"; }
      std::string message(int ev) const { return err::error_code::to_string(ev); }

      static inline std::string message(int e_code, int e_class, confirmed_private_transfer_error_t confirmed_private_transfer_error_) {
        return err::error_class::to_string(e_class) + "::" + err::error_code::to_string(e_code) + ":: xxx to do";
      }

    };
    inline const boost::system::error_category & bacnet_vt_close_error_category() noexcept  {
      static const vt_close_error_category vt_close_error_category_const;
      return vt_close_error_category_const;
    }






////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////  bacnet reject_category
    struct  reject_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::reject"; }
      inline std::string message(int ev) const {
        return err::reject_reason::to_string(ev) ;
      }
    };
    inline const boost::system::error_category & bacnet_reject_category() noexcept  {
      static const reject_category reject_category_const;
      return reject_category_const;
    }


////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////  bacnet abort_category
    struct  abort_category :   public boost::system::error_category   {
      const char *name() const noexcept { return "bacnet::abort"; }
      inline std::string message(int ev) const {
        return err::abort_reason::to_string(ev) ;
      }
    };
    inline const boost::system::error_category & bacnet_abort_category() noexcept  {
      static const abort_category abort_category_const;
      return abort_category_const;
    }

}


#endif /* SRC_BACNET_ERROR_CATEGORY_HPP_ */
