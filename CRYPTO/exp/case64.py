import base64

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
ciphertext = "OoDVP4LtFm7lKnHk+JDrJo2jNZDROl/1HH77H5Xv"

def caesar_decrypt(text, shift):
    table = str.maketrans(alphabet, alphabet[shift:] + alphabet[:shift])
    return text.translate(table)

for shift in range(64):
    candidate = caesar_decrypt(ciphertext, shift)
    try:
        decoded = base64.b64decode(candidate)
        # 判断是否可读文本（可以先试着解码为UTF-8或ASCII）
        try:
            print("Shift:", shift, "Plaintext:", decoded.decode())  # 如果是正常文本会显示出来
        except:
            pass  # 解码不了则跳过
    except:
        pass
