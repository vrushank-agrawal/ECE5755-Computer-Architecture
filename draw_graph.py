import matplotlib
matplotlib.use('TkAgg')  # Use the TkAgg backend

import matplotlib.pyplot as plt
import numpy as np


def draw_0():

    values = [
        [32.5, 12.3, 3.0, 35.2, 32.2, 25.6],
        [7.6, 8.8, 19.3, 7.5, 9.2, 14.1],
        [28.4, 27.2, 24.9, 27.4, 25.7, 20.5],
        [31.5, 51.7, 52.8, 29.9, 33.0, 39.8]
    ]

    colors = ['b', 'r', 'y', 'g']
    labels = ['Frontend bound', 'Bad speculation', 'Backend bound', 'Retiring']
    categories = ['Bubble Sort 100', 'Bubble Sort 1000', 'Bubble Sort 5000', 'MySort 100', 'MySort 1000', 'MySort 5000']

    # Initialize the starting positions for the bars
    bar_position = np.arange(len(categories))

    # Width of each bar
    bar_width = 0.4

    # Create a stacked bar chart with 6 bars
    bottom = np.zeros(len(categories))  # Initialize the bottom values

    for i, values in enumerate(values):
        plt.barh(
            bar_position,
            values,
            height=bar_width,
            label=labels[i],
            left=bottom
        )
        bottom += np.array(values)  # Update the bottom values for stacking

    # Set labels, title, and legend
    plt.xlabel('Pipeline bottleneck breakdown (%)')
    # plt.ylabel('Values')
    plt.yticks(bar_position, categories)

    # display legend outside the plot
    plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)

    # Display the plot
    plt.show()


if __name__ == "__main__":
    draw_0()
