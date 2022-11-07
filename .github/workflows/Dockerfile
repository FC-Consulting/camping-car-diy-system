FROM python:3

RUN python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/6.1.5/scripts/get-platformio.py)"
ENV PATH="/root/.platformio/penv/bin:${PATH}"
RUN platformio platform update