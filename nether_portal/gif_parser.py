from PIL import Image
import numpy as np
import os

"""
320/240 = 20/15 = 4/3
320/16=20
240/16=15
"""


def gif_to_png_resized(gif_path, output_folder, target_size=(16, 16)):
    # 打开GIF文件
    gif = Image.open(gif_path)

    # 创建输出文件夹
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # 用于存储每一帧的数组(去掉Alpha通道)
    frames_array = []

    # 遍历GIF的每一帧
    frame_number = 0
    try:
        while True:
            # 复制当前帧
            frame = gif.copy()

            # 如果是第一帧，跳过
            if frame_number == 0:
                frame_number += 1
                gif.seek(gif.tell() + 1)
                continue

            # 缩放帧到目标大小 (16x16)
            resized_frame = frame.resize(target_size, Image.Resampling.LANCZOS)

            # 将缩放后的帧转换为NumPy数组
            frame_array = np.array(resized_frame)

            # 如果帧有Alpha通道(形状为 (16, 16, 4))，去掉Alpha通道
            if frame_array.shape[-1] == 4:
                frame_array = frame_array[..., :3]  # 只保留前3个通道(RGB)

            # 将数组添加到列表中
            frames_array.append(frame_array)

            if False:
                # 保存缩放后的帧为PNG
                resized_frame.save(
                    os.path.join(output_folder, f"frame_{frame_number:02d}.png"), "PNG"
                )
                frame_number += 1

            # 移动到下一帧
            gif.seek(gif.tell() + 1)
    except EOFError:
        # GIF文件结束
        ...

    # 返回所有帧的数组(去掉Alpha通道)
    return frames_array


def count_unique_colors(gif_path):
    # 打开GIF文件
    gif = Image.open(gif_path)

    # 用于存储所有帧的颜色
    all_colors = []

    try:
        while True:
            # 将当前帧转换为NumPy数组
            frame = np.array(gif)

            # 将帧的形状从 (height, width, channels) 转换为 (height * width, channels)
            # 这样每一行代表一个像素的颜色
            colors = frame.reshape(-1, frame.shape[-1])

            # 将当前帧的颜色添加到所有颜色中
            all_colors.append(colors)

            # 移动到下一帧
            gif.seek(gif.tell() + 1)
    except EOFError:
        # GIF文件结束
        ...

    # 将所有帧的颜色合并为一个数组
    all_colors = np.vstack(all_colors)

    # 统计唯一颜色
    unique_colors = np.unique(all_colors, axis=0)

    # 返回唯一颜色的数量
    return len(unique_colors)


def numpy_to_c_array(frame_array, frame_number):
    # 将NumPy数组转换为C数组格式的字符串
    c_array = f"unsigned char frame_{frame_number}[{frame_array.shape[0]}][{frame_array.shape[1]}][{frame_array.shape[2]}] = {{\n"
    for row in frame_array:
        c_array += "    {"
        for pixel in row:
            c_array += "{" + ", ".join(map(str, pixel)) + "}, "
        c_array = c_array.rstrip(", ") + "},\n"
    c_array = c_array.rstrip(",\n") + "\n};\n"
    return c_array


def numpy_to_c_array_rgb565(frame_array, frame_number):
    # 将NumPy数组转换为C数组格式的字符串(RGB565)
    c_array = "{\n"
    for row in frame_array:
        c_array += "    {"
        for pixel in row:
            r, g, b = pixel
            # print(f"({r}, {g}, {b})") # 第一次测试输出
            # print(type(r), type(g), type(b))
            rgb565 = ((int(r) >> 3) << 11) | ((int(g) >> 2) << 5) | (int(b) >> 3)
            # print(hex(rgb565)) # 第二次测试输出
            c_array += f"0x{rgb565:04x}, "  # 格式化为4位16进制数
        c_array = c_array.rstrip(", ") + "},\n"
    c_array = c_array.rstrip(",\n") + "\n},"
    return c_array


if __name__ == "__main__":
    # 使用示例
    gif_path = "./NetherPortal.gif"  # 替换为你的GIF文件路径
    output_folder = "NetherPortal"  # 替换为你想保存PNG文件的文件夹路径
    # 转换为PNG
    frames_array = gif_to_png_resized(gif_path, output_folder)
    # 输出每一帧的数组为C数组格式(RGB565)
    print("unsigned char frame[29][16][16] = {")
    for i, frame in enumerate(frames_array):
        c_array_str = numpy_to_c_array_rgb565(frame, i + 1)  # i + 1 因为跳过了第一帧
        print(f"{c_array_str}")
    print("};")
