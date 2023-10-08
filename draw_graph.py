import matplotlib
matplotlib.use('TkAgg')  # Use the TkAgg backend

import matplotlib.pyplot as plt
import numpy as np


def draw_0():

    values = []
    # values.append([
    #     [3.3,  0.6,  0.4,  1.0,  0.8,  0.5,  1.1,  2.3,  3.0],
    #     [1.7,  0.7,  0.4,  2.1,  2.0,  0.8,  3.4,  2.8,  1.5],
    #     [4.2,  22.1, 16.3, 12.9, 11.3, 10.8, 9.7,  7.8,  6.9],
    #     [90.8, 76.6, 83.0, 84.0, 85.8, 87.9, 85.9, 87.2, 88.6],
    # ])

    values.append([
        [0.5,  1.6,  0.6,  0.9,  0.7,  0.5,  0.6],
        [0.5,  2.4,  1.1,  2.2,  1.9,  0.7,  0.7],
        [6.1,  21.2, 15.6, 13.3, 11.0, 10.5, 11.5],
        [92.9, 74.8, 82.6, 83.7, 86.3, 88.4, 87.2],
    ])

    # values.append([
    #     [25.1, 24.5, 25.4],
    #     [10.7, 10.9, 10.7],
    #     [32.6, 32.4, 32.1],
    #     [31.6, 32.2, 31.9],
    # ])

    # values.append([
    #     [24.9, 12.6, 0.9],
    #     [10.7, 4.0, 0.1],
    #     [32.4, 57.3, 70.5],
    #     [32.0, 26.1, 28.5],
    # ])

    # values.append([
    #     [13.3, 10.8, 0.3],
    #     [6.2, 5.3, 0.5],
    #     [20.1, 17.6, 6.7],
    #     [60.5, 66.3, 92.6]
    # ])

    # values.append([
    #     [0.1, 0.1, 1.2],
    #     [0.0, 0.0, 3.6],
    #     [32.5, 32.5, 32.8],
    #     [67.4, 67.4, 62.4]
    # ])

    labels = ['Frontend bound', 'Bad speculation', 'Backend bound', 'Retiring']
    categories = []
    # categories.append(['Matmul', '1', '2', '4', '8', '16', '32', '64', '128', '256'])
    # categories.append(['Matmul', '1', '2', '4', '8', '16', '32', '64', '128'])
    categories.append(['Matmul', '1', '2', '4', '8', '16', '32'])
    # categories.append(['Convolution 1', 'Convolution 2', 'Convolution 3'])
    # categories.append(['Relu 1', 'Relu 2', 'Relu 3'])
    # categories.append(['Linear 1', 'Linear 2', 'Linear 3'])
    # categories.append(['Matmul 1', 'Matmul 2', 'Matmul 3'])
    # categories.append(['Softmax 1', 'Softmax 2', 'Softmax 3'])

    # num = 2
    for num in range(1):
        # Initialize the starting positions for the bars
        bar_position = np.arange(len(categories[num]))

        # Width of each bar
        bar_width = 0.4

        # Create a stacked bar chart with 6 bars
        bottom = np.zeros(len(categories[num]))  # Initialize the bottom values

        for i, vals in enumerate(values[num]):
            plt.barh(
                bar_position,
                vals,
                height=bar_width,
                label=labels[i],
                left=bottom
            )
            # Update the bottom values for stacking
            bottom += np.array(vals)

        # Set labels, title, and legend
        plt.title('Profiling matmul_blocking 20x20 matrix')
        plt.xlabel('Pipeline bottleneck breakdown (%)')
        plt.ylabel('Block Size')
        plt.yticks(bar_position, categories[num])
        plt.legend(bbox_to_anchor=(0.8, 1), loc=2, borderaxespad=0.)

        fig = plt.gcf()
        fig.set_size_inches(8, 5)  # Adjust the width and height as needed

        plt.show()


def draw_1():

    blocks = []
    blocks.append([1, 2, 4, 8, 16, 32, 64, 128, 256])
    blocks.append([1, 2, 4, 8, 16, 32, 64, 128])
    blocks.append([1, 2, 4, 8, 16, 32])

    time = []
    time.append([17.067618, 10.092189, 8.261456, 7.423858, 7.175499, 7.281390, 7.182765, 7.337385, 7.750841])
    # 0.656898
    time.append([1.499448, 0.962579, 0.838493, 0.782889, 0.747891, 0.758775, 0.743087, 0.728936])
    # 0.741843
    time.append([1.766454, 1.110912, 0.973923, 0.898500, 0.858309, 0.860491])

    titles = ["1000x1000 matrix", "100x100 matrix", "20x20 matrix"]

    for i in range(3):
        # Initialize the starting positions for the bars
        plt.plot(blocks[i], time[i], marker='o', linestyle='-')

        # Set labels for the x-axis and y-axis
        plt.xlabel('Block-Size')
        plt.ylabel('Time (seconds)')

        # Add a title to the plot
        plt.title(f'Execution Time vs. Block Size ({titles[i]})')

        # Display the plot
        plt.grid(True)
        plt.show()


if __name__ == "__main__":
    # draw_0()
    draw_1()
