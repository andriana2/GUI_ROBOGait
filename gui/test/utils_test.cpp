#include <gtest/gtest.h>
#include "../include/utils.h"
#include <iostream>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QString>
#include <vector>
#include <string>
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

void processJson(const QJsonDocument& doc) {
    // Acceder al objeto JSON
    QJsonObject jsonObj = doc.object();

    // Verificar si "vec_map_name" existe y es un arreglo
    if (jsonObj.contains("vec_map_name") && jsonObj["vec_map_name"].isArray()) {
        // Obtener el array "vec_map_name"
        QJsonArray jsonArray = jsonObj["vec_map_name"].toArray();

        // Verificar el tamaño del array
        std::cout << "Size of vec_map_name array: " << jsonArray.size() << std::endl;

        // Convertir el QJsonArray a un std::vector<std::string>
        std::vector<std::string> vec_map_name;
        for (const auto& item : jsonArray) {
            // Convertir cada item a QString y luego a std::string
            vec_map_name.push_back(item.toString().toStdString());
        }

        // Mostrar el vector resultante
        std::cout << "Vec_map_name contents: " << std::endl;
        for (const auto& map_name : vec_map_name) {
            std::cout << map_name << std::endl;
        }
    } else {
        std::cerr << "Error: 'vec_map_name' no existe o no es un array." << std::endl;
    }
}

TEST(ExtractJSONObjectsTest, main) {
    // Crear un JSON de ejemplo con el formato especificado
    QString jsonString = R"({
        "opt": "MSG",
        "target": "Map_Name",
        "vec_map_name": [
            "my_map_with_nav2.pgm",
            "my_map.pgm",
            "temporal_map1.pgm",
            "temporal_map.pgm"
        ]
    })";

    // Convertir el QString a QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());

    // Verificar si la deserialización fue exitosa
    if (doc.isNull()) {
        std::cerr << "Error al parsear el JSON." << std::endl;
    } else {
        // Procesar el JSON
        processJson(doc);
    }
}

