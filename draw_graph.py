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
        [ 4.0,  0.5,  4.2,  3.3,  4.4,  3.0,  5.1,  3.6,  4.5,  3.2,  4.6,  3.3,  4.2,  2.9],
        [ 6.2,  0.5,  2.1,  1.6,  0.4,  0.3,  0.3,  0.2,  0.2,  0.2,  1.6,  1.4,  0.2,  0.2],
        [59.9,  6.6, 15.2,  3.8, 28.3, 22.6, 17.4,  7.2, 28.5, 19.5, 24.9, 11.8, 32.7, 28.9],
        [29.9, 92.4, 78.5, 91.2, 67.0, 74.1, 77.1, 89.0, 66.8, 77.2, 68.9, 83.5, 62.8, 68.1],
    ])

    # values.append([
    #     [ 3.3,  3.6,  5.5,  6.2,  6.2,  6.3,  6.6,  6.7,  7.1,  7.3],
    #     [ 1.7, 26.8, 41.6, 47.8, 47.3, 44.5, 43.1, 42.6, 41.8, 41.1],
    #     [ 4.2, 13.5, 12.2, 14.1, 18.8, 22.7, 24.2, 24.8, 25.2, 25.3],
    #     [90.8, 55.7, 40.6, 31.9, 27.7, 26.5, 26.2, 26.0, 25.8, 26.6],
    # ])

    # values.append([
    #     [ 2.7,  3.9,  5.8,  6.6,  6.4,  6.5,  6.8,  7.3,  7.7,  8.1],
    #     [ 0.5, 27.4, 42.4, 49.3, 48.2, 45.1, 43.7, 43.3, 42.7, 41.7],
    #     [26.7, 13.3, 11.7, 13.5, 18.8, 22.8, 24.3, 24.7, 25.3, 25.9],
    #     [70.3, 55.4, 40.1, 30.6, 26.6, 25.6, 25.2, 24.7, 24.3, 24.4],
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
    categories.append(['20x30', 'Matmul 20x30', '100x105', 'Matmul 100x105', '500x505', 'Matmul 500x505', '5x1000', 'Matmul 5x1000', '105x1000', 'Matmul 105x1000', '1000x10', 'Matmul 1000x10', '1000x1005', 'Matmul 1000x1005'])
    # categories.append(['Matmul', '1', '2', '4', '8', '16', '32', '64', '128', '256'])
    # categories.append(['Matmul', '1', '2', '4', '8', '16', '32', '64', '128'])
    # categories.append(['Convolution 1', 'Convolution 2', 'Convolution 3'])
    # categories.append(['Relu 1', 'Relu 2', 'Relu 3'])
    # categories.append(['Linear 1', 'Linear 2', 'Linear 3'])
    # categories.append(['Matmul 1', 'Matmul 2', 'Matmul 3'])
    # categories.append(['Softmax 1', 'Softmax 2', 'Softmax 3'])

    # num = 2
    # titles = ["20x20 matrix", "100x100 matrix", "1000x1000 matrix"]
    for num in range(1):
        # Initialize the starting positions for the bars
        bar_position = np.arange(len(categories[0]))

        # Width of each bar
        bar_width = 0.4

        # Create a stacked bar chart and initialize the bottom values
        bottom = np.zeros(len(categories[0]))

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
        plt.title('Profiling matmul_multithreaded')
        plt.xlabel('Pipeline bottleneck breakdown (%)')
        plt.ylabel('Matrix size')
        plt.yticks(bar_position, categories[0])
        plt.legend(bbox_to_anchor=(0.8, 1), loc=2, borderaxespad=0.)
        plt.tight_layout()

        fig = plt.gcf()
        fig.set_size_inches(8, 5)  # Adjust the width and height as needed

        plt.show()


def draw_1():

    blocks = []
    blocks.append(['20x30', '100x105', '500x505', '5x1000', '105x1000', '1000x10', '1000x1005'])
    # blocks.append(['matmul', 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9])
    # blocks.append(['matmul', 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9])

    time = []

    time.append([1.533276, 0.967622, 1.289840, 7.398126, 0.998911, 0.923349, 1.568443])
    time.append([7.426990, 6.532429, 9.625671, 7.402382, 7.430041, 6.823916, 11.191514])
    time.append([5.185191, 4.258292, 6.864214, 10.195670, 4.708476, 4.173648, 6.310125])

    for i in range(1):
        # Initialize the starting positions for the bars
        plt.plot(blocks[0], time[0], marker='o', linestyle='-', label='Single Thread time')
        plt.plot(blocks[0], time[1], marker='o', linestyle='-', label='Total Thread time')
        plt.plot(blocks[0], time[2], marker='o', linestyle='-', label='Matmul time')

        # Set labels for the x-axis and y-axis
        plt.xlabel('Matrix dimension')
        plt.ylabel('Time (seconds)')

        # Add a title to the plot
        plt.title('matmul runtimes')

        # Display the plot
        plt.legend()
        plt.grid(True)
        plt.show()


def draw_pie():
    labels = ['linear', 'matmul', 'convolution_im2col', 'col2im', 'flatten', 'im2col', 'relu', 'init', 'rest']
    # sizes = [88.27, 8.52, 1.10, 0.86, 0.73, 0.23, 0.16, 0.09, 0.04]
    sizes = [85.84, 7.94, 2.34, 1.40, 1.25, 0.58, 0.37, 0.12, 0.16]
    colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b', '#e377c2', '#7f7f7f', '#bcbd22' ]

    fig1, ax1 = plt.subplots()
    wedges, texts, autotexts = ax1.pie(sizes, autopct=lambda p: '{:.1f}%'.format(p) if p >= 2 else '', shadow=False, startangle=90, colors=colors)

    # Only display the percentage if it's >= 1%
    for autotext in autotexts:
        autotext.set_color('white')

    # Add a legend with labels
    plt.legend(labels, title="Functions", bbox_to_anchor=(0.8, 1), loc=2, borderaxespad=0.)

    # Add title
    # plt.title('gprof profiling baseline')
    plt.title('gprof profiling optimized')

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    # draw_0()
    draw_1()
    # draw_pie()
