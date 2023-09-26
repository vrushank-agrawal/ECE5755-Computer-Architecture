import matplotlib
matplotlib.use('TkAgg')  # Use the TkAgg backend

import matplotlib.pyplot as plt
import numpy as np


def draw_0():

    values = []

    values.append([
        [0.4, 1.4, 1.4],
        [0.5, 3.1, 2.6],
        [15.4, 14.4, 15.5],
        [83.7, 81.2, 80.5],
    ])

    values.append([
        [25.1, 24.5, 25.4],
        [10.7, 10.9, 10.7],
        [32.6, 32.4, 32.1],
        [31.6, 32.2, 31.9],
    ])

    values.append([
        [24.9, 12.6, 0.9],
        [10.7, 4.0, 0.1],
        [32.4, 57.3, 70.5],
        [32.0, 26.1, 28.5],
    ])

    values.append([
        [13.3, 10.8, 0.3],
        [6.2, 5.3, 0.5],
        [20.1, 17.6, 6.7],
        [60.5, 66.3, 92.6]
    ])

    values.append([
        [0.1, 0.1, 1.2],
        [0.0, 0.0, 3.6],
        [32.5, 32.5, 32.8],
        [67.4, 67.4, 62.4]
    ])

    labels = ['Frontend bound', 'Bad speculation', 'Backend bound', 'Retiring']
    categories = []
    categories.append(['Convolution 1', 'Convolution 2', 'Convolution 3'])
    categories.append(['Relu 1', 'Relu 2', 'Relu 3'])
    categories.append(['Linear 1', 'Linear 2', 'Linear 3'])
    categories.append(['Matmul 1', 'Matmul 2', 'Matmul 3'])
    categories.append(['Softmax 1', 'Softmax 2', 'Softmax 3'])

    # num = 2
    for num in range(5):
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
        plt.xlabel('Pipeline bottleneck breakdown (%)')
        # plt.ylabel('Values')
        plt.yticks(bar_position, categories[num])

        # display legend outside the plot
        plt.legend(bbox_to_anchor=(1, 1), loc=2, borderaxespad=0.)

        # Display the plot
        plt.show()


if __name__ == "__main__":
    draw_0()
