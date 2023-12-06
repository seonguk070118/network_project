from flask import Flask, render_template, request, jsonify
import pymysql
import serial
from threading import Thread

app = Flask(__name__)

db = pymysql.connect(host='localhost', user='lsy070806', password='12345', db='first', charset='utf8')

com = serial.Serial(
    port="/dev/ttyACM1",
    baudrate=9600,
    bytesize=serial.EIGHTBITS,
    parity=serial.PARITY_NONE,
    timeout=1
)

@app.route('/')
def index():
    cursor = db.cursor()
    sql = "SELECT * FROM drinks"
    cursor.execute(sql)
    drinks = cursor.fetchall()
    return render_template('index.html', drinks=drinks)

@app.route('/update', methods=['POST'])
def update():
    id = request.form['id']
    name = request.form['name']
    stock = request.form['stock']
    price = request.form['price']
    cursor = db.cursor()
    sql = f"UPDATE drinks SET name='{name}', stock={stock}, price={price} WHERE id='{id}'"
    cursor.execute(sql)
    db.commit()
    return jsonify({'result': 'success'})

@app.route('/refresh', methods=['GET'])
def refresh():
    cursor = db.cursor()
    sql = "SELECT * FROM drinks"
    cursor.execute(sql)
    drinks = cursor.fetchall()
    return jsonify({'drinks': drinks})

@app.route('/update_arduino', methods=['POST'])
def update_arduino():
    new_price = request.form['new_price']
    item = request.form['item']
    com.write(f"{item}:{new_price}".encode())  # item은 수정하려는 상품을 의미합니다.
    return jsonify({'result': 'success'})

def read_serial():
    while True:
        read_data = com.read().decode('utf-8', 'ignore')
        if read_data in ['A', 'B', 'C']:
            cursor = db.cursor()
            sql = f"UPDATE drinks SET stock=stock-1 WHERE id='{read_data}'"
            cursor.execute(sql)
            db.commit()

if __name__ == "__main__":
    Thread(target=read_serial).start()
    app.run(host='0.0.0.0', port=5000)
