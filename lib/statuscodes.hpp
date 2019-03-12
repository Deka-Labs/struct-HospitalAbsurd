#ifndef STATUSCODES_HPP
#define STATUSCODES_HPP

enum StatusCodes {
    StatusCode_UNKNOWN = 0, ///< Неизвестная ошибка
    StatusCode_OK, ///< Нет ошибки
    StatusCode_AlreadyExist, ///< Ошибка в следствии попытки добавить то, что уже есть
    StatusCode_Overloaded, ///< Ошибка добавление связаная с переполнением
    StatusCode_WrongMode, ///< Попытка использовать объект в неверном режиме
    StatusCode_File_UnexpectedEnd, ///< Неожиданное завершение файла
    StatusCode_File_NoObject, ///< Для работы отсутсвует объект
    StatusCode_InvalidObject ///< Объект имеет наверные данные
};

#endif // STATUSCODES_HPP
