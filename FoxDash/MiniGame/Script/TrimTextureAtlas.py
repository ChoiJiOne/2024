import json
import sys
import os

if __name__ == '__main__':
    # 명령행 인수 검사.
    if len(sys.argv) != 2:
        print("\n>> Invalid command line argument! <<")
        print("Command syntax: {0} <filename>\n".format(sys.argv[0]))
        sys.exit(0)

    # 파일 유효성 검사.
    target_file_path = sys.argv[1]
    if not os.path.exists(target_file_path):
        print("\n>> No file found at '{0}'\n".format(target_file_path))

    # 텍스처 아틀라스 정보를 포함한 Json 읽기
    texture_atlas_data = {}
    with open(target_file_path) as f:
        json_data = json.load(f)
        keys = json_data['frames'].keys()

        for key in keys:
            name = key
            x = json_data['frames'][key]['frame']['x']
            y = json_data['frames'][key]['frame']['y']
            w = json_data['frames'][key]['frame']['w']
            h = json_data['frames'][key]['frame']['h']

            texture_atlas_data[name] = {}
            texture_atlas_data[name]['x'] = x
            texture_atlas_data[name]['y'] = y
            texture_atlas_data[name]['w'] = w
            texture_atlas_data[name]['h'] = h
    
    # 변환된 Json 오브젝트 저장.
    target_file_name = os.path.splitext(os.path.basename(target_file_path))[0]
    base_path = os.path.dirname(target_file_path)
    target_path = base_path + "\\" + target_file_name + ".atlas"

    with open(target_path, "w", encoding="utf-8") as file:
        json.dump(texture_atlas_data, file, ensure_ascii=False, indent=4)

    print("\n>> Done trim texture atlas json file. <<\n")