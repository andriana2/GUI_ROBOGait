from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = '/home/andri/Desktop/ddbb/db_robogait.db'

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


@app.route('/execute', methods=['POST'])
def execute():
    data = request.json
    query = data.get('query')
    args = data.get('args', ())

    if not query:
        return jsonify({"status": "error", "message": "Falta la consulta SQL"}), 400

    try:
        result = query_db(query, args)
        return jsonify({"status": "success", "result": result})
    except sqlite3.Error as e:
        print("Error en consulta:", str(e))
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

