from flask import Flask, request, jsonify
import sqlite3
import re

app = Flask(__name__)

EN_CASA = True
ROBOT = False

if EN_CASA and not ROBOT:
    DATABASE = "/home/andri/Desktop/gui_nuevo/gui_/server/db_robogait.db"  # casa
elif not ROBOT:
    DATABASE = "/home/robogait/Desktop/gui_andri/GUI_ROBOGait/server/db_robogait.db"  # uni
else:
    DATABASE = "/home/robogait/GUI_ROBOGait/server/db_robogait.db"  # robot

print(DATABASE)

def is_query_safe(query):
    # Lista de palabras clave peligrosas (expandida)
    dangerous_keywords = [
        "DROP",
        "DELETE",
        "ALTER",
        "TRUNCATE",
        "--",
        "/*",
        "*/",
        "xp_",
        "EXEC",
        "MERGE",
    ]

    # # Regex para detectar SQL injection y evitar múltiples sentencias
    # injection_pattern = re.compile(
    #     r"(--|'|\"|/\*|\*/|xp_)|", # Comentarios SQL, caracteres peligrosos
    #     re.IGNORECASE
    # )

    # # Comprobar cuántas veces se encuentran SELECT, INSERT o UPDATE
    # select_count = query.upper().count("SELECT")
    # insert_count = query.upper().count("INSERT")
    # update_count = query.upper().count("UPDATE")

    # # Si hay más de una ocurrencia de SELECT, INSERT o UPDATE, bloquear
    # if select_count > 1 or insert_count > 1 or update_count > 1:
    #     print("more than one select, insert or update")
    #     return False

    # Comprobar si la consulta contiene más de un `;`
    # Permitir una sentencia con un `;` al final
    if query.count(";") > 1 or (
        query.count(";") == 1 and not query.strip().endswith(";")
    ):
        print("more than one ;")
        return False

    # Verificar si contiene palabras clave peligrosas o coincide con el patrón de inyección
    if any(keyword in query.upper() for keyword in dangerous_keywords):
        print("dangerous keywords")
        return False
    # if injection_pattern.search(query):
    #     print("injection pattern")
    #     return False
    return True


def query_db(query, args=(), one=False):
    print("Ejecutando consulta:", query, "con argumentos:", args)
    try:
        conn = sqlite3.connect(DATABASE)
        cur = conn.cursor()
        cur.execute(query, args)  # Si hay error, Flask lo imprimirá
        rv = cur.fetchall()
        conn.commit()
        conn.close()

        return (rv[0] if rv else None) if one else rv
    except Exception as e:
        print("ERROR EN LA CONSULTA:", str(e))
        return None


@app.route("/execute", methods=["POST"])
def execute():
    data = request.json
    target = data.get("target")
    query = data.get("query")
    args = data.get("args", [])

    if not target:
        return jsonify({"status": "error", "message": "Falta el target de la consulta"}), 400

    if not query:
        return jsonify({"status": "error", "message": "Falta la consulta SQL"}), 400

    if not is_query_safe(query):
        return (
            jsonify({"status": "error", "message": "Possible SQL injection attempt"}),
            403,
        )

    try:
        result = query_db(query, args)
        return jsonify({"target": target, "status": "success", "result": result})
    except sqlite3.Error as e:
        print("Error en consulta:", str(e))
        return jsonify({"target": target, "status": "error", "message": str(e)}), 500


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
