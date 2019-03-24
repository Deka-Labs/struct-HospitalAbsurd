#ifndef STATUSCODES_HPP
#define STATUSCODES_HPP

enum StatusCodes {
    StatusCode_UNKNOWN = 0, ///< Неизвестная ошибка
    StatusCode_OK,          ///< Нет ошибки
    StatusCode_AlreadyExist, ///< Ошибка в следствии попытки добавить то, что уже есть
    StatusCode_Overloaded, ///< Ошибка добавление связаная с переполнением
    StatusCode_WrongMode,  ///< Попытка использовать объект в неверном режиме
    StatusCode_File_UnexpectedEnd, ///< Неожиданное завершение файла
    StatusCode_File_NoObject,      ///< Для работы отсутсвует объект
    StatusCode_InvalidObject,      ///< Объект имеет наверные данные
    StatusCode_File_InvalidFormat, ///< Неверный формат файла
    StatusCodes_File_NotOpened,    ///< Файл не был открыт
    StatusCodes_File_NotExist,     ///< Файл не найден
    StatusCodes_SIZE
};

static const char* g_STATUSCODES_MESSAGES[StatusCodes_SIZE] = {
    "Неизветная ошибка",            ///< StatusCode_UNKNOWN
    "Нет ошибки",                   ///< StatusCode_OK
    "Объект уже существует",        ///< StatusCode_AlreadyExist
    "Переполнение",                 ///< StatusCode_Overloaded
    "Неверный режим работы",        ///< StatusCode_WrongMode
    "Неожиданное завершение файла", ///< StatusCode_File_UnexpectedEnd
    "Нет объекта для чтения",       ///< StatusCode_File_NoObject
    "Неверный объект",              ///< StatusCode_InvalidObject
    "Неверный формат файла",        ///< StatusCode_File_InvalidFormat
    "Файл не был открыт",           ///< StatusCodes_File_NotOpened
    "Файл не найден"                ///< StatusCodes_File_NotExist
};

#endif // STATUSCODES_HPP
