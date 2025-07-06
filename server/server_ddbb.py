from flask import Flask, request, jsonify
import sqlite3
import sys

app = Flask(__name__)

EN_CASA = True
ROBOT = False

if len(sys.argv) != 2:
    print("Uso: python3 server_ddbb.py <ruta_a_base_de_datos>")
    sys.exit(1)

DATABASE = sys.argv[1]
print("Usando base de datos:", DATABASE)
print(DATABASE)

def is_query_safe(query):
    # Lista de palabras clave peligrosas (expandida)
    dangerous_keywords = [
        "DROP",
        "ALTER",
        "TRUNCATE",
        "--",
        "/*",
        "*/",
        "xp_",
        "EXEC",
        "MERGE",
    ]

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
