#include <gtest/gtest.h>
#include "../include/utils.h"
#include <iostream>
/*
TEST(obtein_ip, EXPECT_EQ)
{
    EXPECT_EQ("192.168.0.2", obtenerIP()); // interiores
    EXPECT_EQ("192.168.1.137", obtenerIP()); // exteriores
}*/

TEST(ExtractJSONObjectsTest, ValidInput) {
    QString input = R"({"key1": "value1"}{"key2": "value2"}{"key3": "value3"})";
    QVector<QString> expected = {
        R"({"key1": "value1"})",
        R"({"key2": "value2"})",
        R"({"key3": "value3"})"
    };

    QVector<QString> result = extractJSONObjects(input);

    ASSERT_EQ(result.size(), expected.size()) << "El tamaño del resultado no coincide con el esperado.";

    for (int i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], expected[i]) << "El objeto JSON en la posición " << i << " no coincide.";
    }
}

TEST(ExtractJSONObjectsTest, EmptyInput) {
    QString input = "";
    QVector<QString> expected = {};

    QVector<QString> result = extractJSONObjects(input);

    EXPECT_EQ(result.size(), expected.size()) << "El resultado debería ser un vector vacío.";
}

TEST(ExtractJSONObjectsTest, InvalidJSONFormat) {
    QString input = R"(Invalid JSON string)";
    QVector<QString> expected = {}; // Ningún JSON válido extraído

    QVector<QString> result = extractJSONObjects(input);

    EXPECT_EQ(result.size(), expected.size()) << "El resultado debería ser un vector vacío para cadenas no válidas.";
}

TEST(ExtractJSONObjectsTest, NestedJSONObjects) {
    QString input = R"({"key1": {"nestedKey": "nestedValue"}}{"key2": "value2"})";
    QVector<QString> expected = {
        R"({"key1": {"nestedKey": "nestedValue"}})",
        R"({"key2": "value2"})"
    };

    QVector<QString> result = extractJSONObjects(input);
    
	//for (auto res : result){std::cout << res.toStdString() << std::endl;}
    
    
    ASSERT_EQ(result.size(), expected.size()) << "El tamaño del resultado no coincide con el esperado.";

    for (int i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], expected[i]) << "El objeto JSON en la posición " << i << " no coincide.";
    }
}
