from flask import Flask, render_template, redirect, request, url_for, render_template_string, jsonify
from challenge.encryption import DES3_enc, encrypt_key

FLAG = b'HTB{This is a dummy flag}'
secret_PIN = '841'

app = Flask(__name__)

@app.route('/api/encrypt', methods=['GET'])
def encrypt():	
	msg = bytes.fromhex(request.json.get('msg'))
	
	token = request.json.get('token')
	
	key = encrypt_key(token, secret_PIN)
	try:
		ct = DES3_enc(key, msg)
	except Exception as e:
		if 'DES key' in str(e):
			return jsonify({'status': 'key_error', 'message': 'Your security token is too weak or invalid. Please try another one'})
	return jsonify({'status': 'success', 'ct': ct})


@app.route('/api/flag', methods=['GET'])
def flag():	
	token = request.json.get('token')
	key = encrypt_key(token, secret_PIN)
	try:
		ct = DES3_enc(key, FLAG)
	except Exception as e:
		if 'DES key' in str(e):
			return jsonify({'status': 'key_error', 'message': 'Your security token is too weak or invalid. Please try another one'})
	return jsonify({'status': 'success', 'ct': ct})



if __name__ == '__main__':
	app.run(host ='0.0.0.0',debug=False)
