/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Error
*/

#ifndef ERROR_HPP_
    #define ERROR_HPP_
    #include <iostream>
    
class Error : public std::exception {
    public:
        /// @brief Creates a throwable Error
        /// @param msg Error message
        Error(const std::string &msg) : _msg(msg) {};
        const char *what() const noexcept override { return _msg.c_str(); };

    private:
        const std::string _msg;
};

#endif /* !ERROR_HPP_ */
