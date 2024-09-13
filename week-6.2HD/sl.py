import streamlit as st
import pandas as pd
import numpy as np
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import time

# Set page configuration
st.set_page_config(page_title="Gyroscope Data Dashboard", layout="wide")

# Function to load data from CSV
@st.cache_data
def load_data():
    df = pd.read_csv('gyroscope_data-1.csv')
    # Assuming the first column is timestamp, convert it to datetime
    df.iloc[:, 0] = pd.to_datetime(df.iloc[:, 0])
    return df

# Load data
if 'data' not in st.session_state:
    st.session_state.data = load_data()
    st.session_state.sample_start = 0

# Get actual column names
timestamp_col = st.session_state.data.columns[0]
data_cols = st.session_state.data.columns[1:]

# Sidebar for controls
st.sidebar.title("Controls")
graph_type = st.sidebar.selectbox("Graph Type", ['Line', 'Scatter', 'Distribution'])
y_axis = st.sidebar.selectbox("Y-axis", ['all'] + list(data_cols))
samples = st.sidebar.number_input("Number of Samples", min_value=10, max_value=len(st.session_state.data), value=100)

# Main content
st.title("Gyroscope Data Visualization")

# Create a placeholder for the plot
plot_placeholder = st.empty()

# Define colors for each axis
colors = {data_cols[0]: 'red', data_cols[1]: 'green', data_cols[2]: 'blue'}

# Function to update the plot
def update_plot():
    df_subset = st.session_state.data.iloc[st.session_state.sample_start:st.session_state.sample_start+samples]
    
    fig = make_subplots(rows=1, cols=1)

    if graph_type == 'Distribution':
        for col in data_cols:
            if y_axis == 'all' or y_axis == col:
                fig.add_trace(go.Histogram(x=df_subset[col], name=col, marker_color=colors[col]))
    else:
        for col in data_cols:
            if y_axis == 'all' or y_axis == col:
                if graph_type == 'Line':
                    fig.add_trace(go.Scatter(x=df_subset[timestamp_col], y=df_subset[col], mode='lines', name=col, line=dict(color=colors[col])))
                else:  # Scatter
                    fig.add_trace(go.Scatter(x=df_subset[timestamp_col], y=df_subset[col], mode='markers', name=col, marker=dict(color=colors[col])))

    fig.update_layout(
        title="Gyroscope Data",
        xaxis_title="Timestamp" if graph_type != 'Distribution' else "Value",
        yaxis_title="Value" if graph_type != 'Distribution' else "Count",
        legend_title="Axis",
        height=600
    )

    plot_placeholder.plotly_chart(fig, use_container_width=True)

    # Display statistics
    st.subheader("Statistics")
    stats = {col: [f"{df_subset[col].mean():.2f}", f"{df_subset[col].median():.2f}", f"{df_subset[col].std():.2f}"] for col in data_cols}
    stats_df = pd.DataFrame(stats, index=['Mean', 'Median', 'Std Dev'])
    st.table(stats_df)

    # Display current range
    st.write(f"Displaying samples {st.session_state.sample_start} to {st.session_state.sample_start + samples} out of {len(st.session_state.data)}")

# Update plot initially
update_plot()

# Add navigation buttons
col1, col2 = st.columns(2)
with col1:
    if st.button("Previous"):
        st.session_state.sample_start = max(0, st.session_state.sample_start - samples)
        update_plot()
with col2:
    if st.button("Next"):
        st.session_state.sample_start = min(len(st.session_state.data) - samples, st.session_state.sample_start + samples)
        update_plot()

# Display raw data
if st.checkbox("Show Raw Data"):
    st.subheader("Raw Data")
    st.dataframe(st.session_state.data.iloc[st.session_state.sample_start:st.session_state.sample_start+samples])

# Add auto-update feature
if st.sidebar.checkbox("Enable Auto-update"):
    st.write("Auto-updating every 10 seconds...")
    while True:
        time.sleep(10)
        st.session_state.sample_start = (st.session_state.sample_start + samples) % (len(st.session_state.data) - samples)
        update_plot()
        st.experimental_rerun()