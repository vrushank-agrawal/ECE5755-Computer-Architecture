import matplotlib
matplotlib.use('TkAgg')  # Use the TkAgg backend

import matplotlib.pyplot as plt
import numpy as np


def draw_0():

    values = []
    values.append([
        [0.2, 0.2, 0.9, 0.3, 0.4, 1.1, 2.3, 2.8, 2.9],
        [0.1, 0.1, 1.9, 0.4, 0.7, 3.6, 2.2, 1.1, 0.6],
        [35.4, 24.2, 16.0, 13.1, 11.6, 10.0, 9.4, 12.0, 16.9],
        [64.3, 75.5, 81.3, 86.2, 87.3, 85.3, 86.1, 84.1, 79.5],
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
    categories.append(['1', '2', '4', '8', '16', '32', '64', '128', '256'])
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
        plt.title('Profiling matmul_blocking')
        plt.xlabel('Pipeline bottleneck breakdown (%)')
        plt.ylabel('Block Size')
        plt.yticks(bar_position, categories[num])
        plt.legend(bbox_to_anchor=(0.8, 1), loc=2, borderaxespad=0.)

        fig = plt.gcf()
        fig.set_size_inches(8, 5)  # Adjust the width and height as needed

        plt.show()


def draw_1():

    blocks = [1, 2, 4, 8, 16, 32, 64, 128, 256]
    time = [17.067618, 10.092189, 8.261456, 7.423858, 7.175499, 7.281390, 7.182765, 7.337385, 7.750841]

    plt.plot(blocks, time, marker='o', linestyle='-')

    # Set labels for the x-axis and y-axis
    plt.xlabel('Number of Blocks')
    plt.ylabel('Time (seconds)')

    # Add a title to the plot
    plt.title('Execution Time vs. Block Size')

    # Display the plot
    plt.grid(True)
    plt.show()


if __name__ == "__main__":
    draw_0()
    # draw_1()
