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
        [ 0.5,  2.2,  4.3,  5.5,  5.6,  5.7,  5.5,  5.3,  4.4,  1.2],
        [ 0.5, 15.6, 32.5, 43.2, 43.5, 41.0, 37.1, 32.0, 24.8,  3.3],
        [ 4.2, 15.3, 13.9, 14.1, 19.0, 22.0, 24.2, 25.8, 28.3, 34.6],
        [92.9, 66.6, 49.3, 37.1, 31.9, 31.4, 33.3, 36.9, 42.6, 57.0],
    ])

    values.append([
        [ 3.3,  3.6,  5.5,  6.2,  6.2,  6.3,  6.6,  6.7,  7.1,  7.3],
        [ 1.7, 26.8, 41.6, 47.8, 47.3, 44.5, 43.1, 42.6, 41.8, 41.1],
        [ 4.2, 13.5, 12.2, 14.1, 18.8, 22.7, 24.2, 24.8, 25.2, 25.3],
        [90.8, 55.7, 40.6, 31.9, 27.7, 26.5, 26.2, 26.0, 25.8, 26.6],
    ])

    values.append([
        [ 2.7,  3.9,  5.8,  6.6,  6.4,  6.5,  6.8,  7.3,  7.7,  8.1],
        [ 0.5, 27.4, 42.4, 49.3, 48.2, 45.1, 43.7, 43.3, 42.7, 41.7],
        [26.7, 13.3, 11.7, 13.5, 18.8, 22.8, 24.3, 24.7, 25.3, 25.9],
        [70.3, 55.4, 40.1, 30.6, 26.6, 25.6, 25.2, 24.7, 24.3, 24.4],
    ])

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
    categories.append(['Matmul', '0.1', '0.2', '0.3', '0.4', '0.5', '0.6', '0.7', '0.8', '0.9'])
    # categories.append(['Convolution 1', 'Convolution 2', 'Convolution 3'])
    # categories.append(['Relu 1', 'Relu 2', 'Relu 3'])
    # categories.append(['Linear 1', 'Linear 2', 'Linear 3'])
    # categories.append(['Matmul 1', 'Matmul 2', 'Matmul 3'])
    # categories.append(['Softmax 1', 'Softmax 2', 'Softmax 3'])

    # num = 2
    titles = ["20x20 matrix", "100x100 matrix", "1000x1000 matrix"]
    for num in range(1):
        # Initialize the starting positions for the bars
        bar_position = np.arange(len(categories[0]))

        # Width of each bar
        bar_width = 0.4

        # Create a stacked bar chart with 6 bars
        bottom = np.zeros(len(categories[0]))  # Initialize the bottom values

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
        plt.title(f'Profiling matmul_sparse {titles[num]}')
        plt.xlabel('Pipeline bottleneck breakdown (%)')
        plt.ylabel('Block Size')
        plt.yticks(bar_position, categories[0])
        plt.legend(bbox_to_anchor=(0.8, 1), loc=2, borderaxespad=0.)

        fig = plt.gcf()
        fig.set_size_inches(8, 5)  # Adjust the width and height as needed

        plt.show()


def draw_1():

    blocks = []
    blocks.append(['matmul', 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9])
    blocks.append(['matmul', 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9])
    blocks.append(['matmul', 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9])

    time = []

    # 13.364708
    time.append([13.364708, 11.113602, 13.119845, 16.288636, 13.728372, 11.259597, 8.935291, 7.042263, 4.709917, 2.748128])
    # time.append([17.067618, 10.092189, 8.261456, 7.423858, 7.175499, 7.281390, 7.182765, 7.337385, 7.750841])
    # 0.656898
    time.append([0.656898, 1.088363, 1.143518, 1.301299, 1.215436, 1.193215, 0.795020, 0.633177, 0.565055, 0.288351])
    # time.append([1.499448, 0.962579, 0.838493, 0.782889, 0.747891, 0.758775, 0.743087, 0.728936])
    # 0.741843
    time.append([0.741843, 0.736861, 0.955316, 1.028136, 0.841390, 0.505078, 0.392630, 0.277656, 0.175522, 0.105911])
    # time.append([1.766454, 1.110912, 0.973923, 0.898500, 0.858309, 0.860491])

    titles = ["1000x1000 matrix", "100x100 matrix", "20x20 matrix"]

    for i in range(3):
        # Initialize the starting positions for the bars
        plt.plot(blocks[i], time[i], marker='o', linestyle='-')

        # Set labels for the x-axis and y-axis
        plt.xlabel('Sparsity ratio')
        plt.ylabel('Time (seconds)')

        # Add a title to the plot
        plt.title(f'Execution Time vs. Matrix Sparcity ({titles[i]})')

        # Display the plot
        plt.grid(True)
        plt.show()


if __name__ == "__main__":
    draw_0()
    # draw_1()
