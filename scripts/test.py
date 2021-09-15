from aip import AipSpeech

APP_ID = "24850239"
APP_KEY = "FFoMeVN2Z7UkCZS4iWnCo0yq"
SECRET_KEY = "47huGqVM0t6ZSSLI9KPBcc2FIGMQrhAv"

def generateMP3(text, client, volume=5, speed=5, pit=5, per=3):
    result = client.synthesis(text, 'zh', 1, {'vol':volume, 'spd':speed, 'pit':pit, 'per':per})
    if not isinstance(result, dict):
        with open("tmp.audio.mp3", "wb") as f:
            f.write(result)

client = AipSpeech(APP_ID, APP_KEY, SECRET_KEY)
generateMP3("这是X射线衍射物相分析虚拟仿真实验的自动生成字幕测试. 衬衫的价格是九镑十五便士,因此,你选择C项", client)
