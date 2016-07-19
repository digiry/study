FROM ubuntu:latest
MAINTAINER Kyujin Kang "digiry@gmail.com"

RUN apt-get update -y && apt-get install -y \
	python-pip \
	python-dev \
	build-essential \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY app.py /app
COPY requirements.txt /app

RUN pip install -r requirements.txt

ENTRYPOINT ["python"]
CMD ["app.py"]

